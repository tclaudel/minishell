#include "minishell.h"

void	builtin_env(t_sh *sh)
{
	size_t	i;

	i = 0;
	while (sh->env[i].key)
	{
		ft_dprintf(1, "%s", sh->env[i].key);
		ft_dprintf(1, "%s", "=");
		ft_dprintf(1, "%s\n", sh->env[i].value);
		i++;
	}
}