#include "minishell.h"

void	parse_redirections()
{
	size_t		i;
	
	i = 0;
	if (ft_strchr(sh()->pipes, '|') && sh()->cmd[i][0] && sh()->cmd[i + 1])
		ft_pipe(&i);
}

void	redirections(void)
{
	pipes_counter();
	parse_redirections();
}