#include "minishell.h"

int		lonely_command(int i, int in_fd)
{
	pid_t		pid;

	if (!is_builtin(sh()->cmd[i][0]))
	{
		pid = fork();
		if (pid == 0)
		{
			if (sh()->redir[(i)] == '>' || sh()->redir[(i)] == 'd')
				right_redir(&i);
			else
			{
				redirect(sh()->fd[1], 1);
				ft_exec(i);
			}
			if (i > 0)
				close(in_fd);
			exit(EXIT_SUCCESS);
		}
	}
	else
		ft_exec(i);
	return (EXIT_SUCCESS);
}
