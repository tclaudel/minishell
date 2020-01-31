#include "minishell.h"

int		get_env_var(t_sh *sh, char **env)
{
	static size_t	i = 0;
	size_t			j;

	while (env[i])
		i++;
	if ((sh->key = (char **)malloc(sizeof(char *) * (i + 1))) &&
	(sh->value = (char **)malloc(sizeof(char *) * (i + 1))))
	{
		i = 0;
		while (env[i])
		{
			j = 0;
			while (env[i][j] && env[i][j] != '=')
				j++;
			sh->key[i] = ft_strndup(env[i], j);
			sh->value[i] = ft_strdup(env[i] + j + 1);
			i++;
		}
		sh->key[i] = NULL;
		sh->value[i] = NULL;
		sh->env = ft_strhash(sh->key, sh->value);
		sh->path = ft_split(ft_get_hash_value(sh->env, "PATH"), ':');
		return (0);
	}
	exit(EXIT_FAILURE);
}
