#include "minishell.h"

void	parsing(t_sh *sh, char *str)
{
	size_t	i;

	i = 0;
	sh->cmd = ft_split(str, ' ');
	// while (sh->cmd[i])
	// {
	// 	printf("cmd[i]\t: %s\n", sh->cmd[i]);
	// 	i++;
	// }
}
