#include "minishell.h"

int		lonely_command(int i, int in_fd)
{
	pid_t		pid;

	if (!is_builtin(sh()->cmd[i][0]))
	{
		pid = fork();
		if (pid == 0)
		{
			if (sh()->pipes[(i)] == '>' || sh()->pipes[(i)] == 'd')
			{
				sh()->fd[1] = right_redir(i);
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
