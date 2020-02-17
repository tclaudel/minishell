#include "minishell.h"

static void			search_pwd(void)
{
	char			str[1024];
	char			**splited;

	if (!change_value(get_sh_info()->env, "PWD", getcwd(str, 1024)))
	{
		splited = ft_split(ft_strfjoin("export ",
		ft_strfjoin(ft_strjoin("PWD", "="), getcwd(str, 1024), 1), 2), ' ');
		builtin_export(get_sh_info(), splited);
		ft_free_tab(splited);
	}
}

int					get_env_var(t_sh *sh, char **env)
{
	size_t	i;
	size_t	j;

	i = ft_tablen(env);
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
		search_pwd();
		return (0);
	}
	exit(EXIT_FAILURE);
}

t_strhash			*realloc_hash(t_strhash *hash, size_t size)
{
	size_t		i;
	t_strhash	*new;

	i = 0;
	if (!(new = (t_strhash *)ft_calloc(size, 1)))
		return (NULL);
	while (hash[i].key)
	{
		new[i] = hash[i];
		i++;
	}
	free(hash);
	return (new);
}

void				replace_env_var(t_sh *sh, char **cmd, size_t i)
{
	size_t	j;
	char	*buf;
	char	*tmp;

	while (cmd[i])
	{
		if (cmd[i][0] == '$')
		{
			buf = ft_strdup(cmd[i]);
			j = ft_tablen(cmd) - 1;
			ft_strdel(&cmd[i]);
			if (ft_get_hash_value(sh->env, buf + 1))
				cmd[i] = ft_strdup(ft_get_hash_value(sh->env, buf + 1));
			else
			{
				cmd[i] = NULL;
				tmp = cmd[j];
				cmd[j] = cmd[i];
				cmd[i] = tmp;
			}
			ft_strdel(&buf);
		}
		i++;
	}
}
