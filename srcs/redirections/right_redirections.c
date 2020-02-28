#include "minishell.h"

int		redirect_output(int i)
{
	int fd;

	if (!(fd = open(sh()->cmd[i + 1][0], sh()->pipes[i] == 'd' ?
		O_RDWR | O_CREAT | O_APPEND : O_RDWR | O_CREAT | O_TRUNC, 0644)))
		return (-1);
	if (dup2(fd, STDOUT_FILENO) < 1)
		return (-1);
	return (fd);
}

int		right_redir(int i)
{
	int fd;

	fd = redirect_output(i);
	return (fd);
}
