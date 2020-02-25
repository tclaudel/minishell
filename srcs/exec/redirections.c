#include "minishell.h"

void	ft_pipe(size_t *i)
{
	pid_t	pid;
	int		status;
	int		stdin_bkp;

	status = 0;
	stdin_bkp = dup(STDIN_FILENO);
	if (pipe(sh()->fd))
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		ft_dprintf(2, "%s\n", strerror(errno));
	if (pid == 0)
	{
		dup2(sh()->fd[1], STDOUT_FILENO);
		close(sh()->fd[1]);
		ft_exec((*i));
		(*i)++;
		exit(1);
	}
	(*i)++;
	dup2(sh()->fd[0], STDIN_FILENO);
	close(sh()->fd[0]);
	ft_exec((*i));
	dup2(stdin_bkp, STDIN_FILENO);
	close(sh()->fd[1]);
}
