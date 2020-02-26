#include "minishell.h"

void	parse_redirections(void)
{
	size_t		i;

	i = 0;
	if (ft_strchr(sh()->pipes, '|') && sh()->cmd[i][0] && sh()->cmd[i + 1])
		ft_pipe(&i);
	dup2(sh()->stdin_bkp, STDIN_FILENO);
	close(sh()->fd[0]);
}

void	redirections(void)
{
	pipes_counter();
	parse_redirections();
}
