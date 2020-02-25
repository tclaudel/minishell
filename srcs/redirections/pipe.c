#include "minishell.h"

void	first_part_of_pipe(size_t *i)
{
	dup2(sh()->fd[1], STDOUT_FILENO);
	close(sh()->fd[0]);
	close(sh()->fd[1]);
	ft_exec((*i));
	exit(1);
}

void	second_part_of_pipe(size_t *i)
{
	close(sh()->fd[1]);
	dup2(sh()->fd[0], STDIN_FILENO);
	ft_exec((*i) + 1);
}

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
		first_part_of_pipe(i);
	wait(NULL);
	second_part_of_pipe(i);
	wait(NULL);
	dup2(stdin_bkp, STDIN_FILENO);
	close(sh()->fd[0]);
}

void	pipes_counter(void)
{
	size_t		i;

	i =
	sh()->pipes_nb = 0;
	while(sh()->pipes[i])
	{
		if (sh()->pipes[i] == '|')
			sh()->pipes_nb++;
		i++;
	}
}
