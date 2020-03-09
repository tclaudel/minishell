#include "minishell.h"

void	redirect(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) == -1)
			close(oldfd);
	}
}

void	exec_child(int i, int in_fd)
{
	close(sh()->fd[0]);
	redirect(in_fd, STDIN_FILENO);
	if ((sh()->redir[(i)] == '>' || sh()->redir[i] == 'd'))
		right_redir(&i);
	else if (sh()->redir[(i)] == '<')
		left_redir(&i);
	else
	{
		redirect(sh()->fd[1], 1);
		ft_exec(i);
	}
	exit(EXIT_SUCCESS);
}

void	exec_father(int i, int in_fd)
{
	int		saved;

	saved = i;
	if (i > 0)
		close(in_fd);
	while (sh()->redir[i] && sh()->redir[i] != '|')
		i++;
	if (ft_strchr(sh()->redir + saved, '|'))
		i++;
	close(sh()->fd[1]);
	redirections(i, sh()->fd[0]);
}

void	redirections(int i, int in_fd)
{
	pid_t	pid;

	if (!sh()->cmd[i + 1])
		i > 0 ? final_redir(i, in_fd) : lonely_command((size_t)i, in_fd);
	else
	{
		sh()->stdin_bkp = dup(STDIN_FILENO);
		if (pipe(sh()->fd))
			ft_exit(EXIT_FAILURE, i);
		pid = fork();
		if (pid == -1)
			ft_dprintf(2, "%s\n", strerror(errno));
		if (pid == 0)
			exec_child(i, in_fd);
		wait(NULL);
		exec_father(i, in_fd);
	}
	wait(NULL);
	dup2(sh()->stdin_bkp, STDIN_FILENO);
	close(sh()->fd[0]);
}
