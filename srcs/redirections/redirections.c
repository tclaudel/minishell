#include "minishell.h"

void	parse_redirections(void)
{
	ft_pipe(0, 0);
}

void	redirections(void)
{
	pipes_counter();
	parse_redirections();
}
