#include "minishell.h"

void redirect(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) == -1)
			close(oldfd);
	}
}

void is_pipe(int i, int in_fd)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		redirect(in_fd, STDIN_FILENO);
		close(sh()->fd[1]);
		ft_exec(i);
		exit(EXIT_SUCCESS);
	}
	close(in_fd);
}

void exec_child(int i, int in_fd)
{
	close(sh()->fd[0]);
	redirect(in_fd, STDIN_FILENO);
	redirect(sh()->fd[1], 1);
	ft_exec(i);
	exit(EXIT_FAILURE);
}

void exec_father(int i, int in_fd)
{
	if (i > 0)
		close(in_fd);
	close(sh()->fd[1]);
	ft_pipe(i + 1, sh()->fd[0]);
}

void	ft_pipe(int i, int in_fd)
{
	pid_t	pid;

	if (!sh()->cmd[i + 1])
	{
		if (i > 0)
			is_pipe(i, in_fd);
		else
			ft_exec((size_t)i);
		wait(NULL);
	}
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
		else
		{
			wait(NULL);
			exec_father(i, in_fd);
		}
	}
	dup2(sh()->stdin_bkp, STDIN_FILENO);
	close(sh()->fd[0]);
}

void	pipes_counter(void)
{
	size_t		i;

	i =
	sh()->pipes_nb = 0;
	while (sh()->pipes[i])
	{
		if (sh()->pipes[i] == '|')
			sh()->pipes_nb++;
		i++;
	}
}
