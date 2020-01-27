#include "minishell.h"

void	parsing(char *str)
{
	t_sh	*sh;
	size_t	i;

	i = 0;
	sh = (t_sh *)malloc(sizeof(t_sh));
	sh->cmd = ft_split(str, ' ');
	while (sh->cmd[i])
	{
		printf("cmd[i]\t: %s\n", sh->cmd[i]);
		i++;
	}
}
