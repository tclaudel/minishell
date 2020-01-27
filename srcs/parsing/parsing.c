#include "minishell.h"

void	parsing(t_sh *sh, char *str)
{
	size_t	i;

	i = 0;
	sh->cmd = ft_split(str, ' ');
	if (sh->cmd[0])
		sh->cmd[0] = ft_strfjoin("/bin/", sh->cmd[0], 2);
}
