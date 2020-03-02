#include "minishell.h"

void	redirect(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) == -1)
			close(oldfd);
	}
}

void	is_pipe(int i, int in_fd)
{
	pid_t pid;

	if (sh()->pipes[(i - 1)] == '|')
	{
		pid = fork();
		if (pid == 0)
		{
			redirect(in_fd, STDIN_FILENO);
			if (sh()->pipes[i] == '>' || sh()->pipes[i] == 'd')
				right_redir(&i);
			else
			{
				redirect(sh()->fd[1], 1);
				ft_exec(i);
			}
			close(sh()->fd[1]);
			exit(EXIT_SUCCESS);
		}
	}
	close(in_fd);
}

void	exec_child(int i, int in_fd)
{
	close(sh()->fd[0]);
	redirect(in_fd, STDIN_FILENO);
	if (sh()->pipes[(i)] == '>' || sh()->pipes[i] == 'd')
		right_redir(&i);
	else
	{
		redirect(sh()->fd[1], 1);
		ft_exec(i);
	}
	exit(EXIT_FAILURE);
}

void	exec_father(int i, int in_fd)
{
	size_t	j;

	j = 0;
	while (sh()->pipes[(j)] == '>' || sh()->pipes[j] == 'd')
		j++;
	dprintf(1, "j\t: %zu\n", j);
	if (i > 0)
		close(in_fd);
	close(sh()->fd[1]);
	dprintf(1, "i\t: %d\n", i);
	ft_pipe(i + 1 + (j == 0 ? 0 : j - 1), sh()->fd[0]);
}

void	ft_pipe(int i, int in_fd)
{
	pid_t	pid;

	if (!sh()->cmd[i + 1])
		i > 0 ? is_pipe(i, in_fd) : lonely_command((size_t)i, in_fd);
	else
	{
		sh()->stdin_bkp = dup(STDIN_FILENO);
		if (pipe(sh()->fd))
			exit(EXIT_FAILURE);
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
