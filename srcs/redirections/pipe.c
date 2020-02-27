#include "minishell.h"

void redirect(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) == -1)
			close(oldfd);
	}
}

int redirect_output(int i)
{
	int fd;

	dprintf(1, "fd\t: %s\n", sh()->cmd[i + 1][0]);
	if (!(fd = open(sh()->cmd[i + 1][0], O_RDWR | O_CREAT | O_TRUNC, 0644)))
		return (-1);
	if (dup2(fd, STDOUT_FILENO) < 1)
		return (-1);
	return (fd);
}

int	left_redir(int i)
{
	int fd;

	fd = redirect_output(i);
	return (1);
}

void is_pipe(int i, int in_fd)
{
	pid_t pid;

	if (sh()->pipes[(i - 1)] == '|')
	{
		pid = fork();
		if (pid == 0)
		{
			redirect(in_fd, STDIN_FILENO);
			if (sh()->pipes[i] == '>')
			{
				dprintf(1, "here");
				sh()->fd[1] = left_redir(i);
			}
			close(sh()->fd[1]);
			ft_exec(i);
			exit(EXIT_SUCCESS);
		}
	}
	close(in_fd);
}

int	exec_child(int *i, int in_fd)
{
	int	ret;

	ret = 0;
	dprintf(1, "pipes\t: %s\n", sh()->pipes + (*i));
	close(sh()->fd[0]);
	redirect(in_fd, STDIN_FILENO);
	if (sh()->pipes[(*i)] == '>')
	{
		sh()->fd[1] = left_redir((*i));
		ret = 1;
	}
	else
		redirect(sh()->fd[1], 1);
	ft_exec((*i));
	exit(EXIT_FAILURE);
	dprintf(1, "ret\t: %d\n", ret);
	return (ret);
}

void	exec_father(int i, int in_fd)
{
	if (i > 0)
		close(in_fd);
	close(sh()->fd[1]);
	ft_pipe(i + 1, sh()->fd[0]);
}

int		lonely_command(int i, int in_fd)
{
	pid_t		pid;

	dprintf(1, "pipes\t: %s\n", sh()->pipes + i);
	if (!is_builtin(sh()->cmd[i][0]))
	{
		pid = fork();
		if (pid == 0)
		{
			if (sh()->pipes[i] == '>')
			{
				sh()->fd[1] = left_redir(i);
			}
			else
				redirect(in_fd, STDIN_FILENO);
			if (i > 0)
				close(in_fd);
			ft_exec(i);
			exit(EXIT_SUCCESS);
		}
	}
	else
		ft_exec(i);
	return (EXIT_SUCCESS);
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
			i += exec_child(&i, in_fd);
		else
		{
			// dprintf(1, "i\t: %d\n", i);
			wait(NULL);
			exec_father(i, in_fd);
		}
	}
	wait(NULL);
	dup2(sh()->stdin_bkp, STDIN_FILENO);
	close(sh()->fd[0]);
}
