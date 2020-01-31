#include "minishell.h"

void		builtin_env(t_sh *sh)
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

void		builtin_export(t_sh *sh, char **key)
{
	size_t j;
	size_t k;
	size_t i;

	j = 1;
	i = 0;
	while (sh->env[i].key)
		i++;
	while (key[j])
		j++;
	sh->env = realloc_hash(sh->env, sizeof(t_strhash) * (i + j));
	j = 1;
	while (key[j])
	{
		k = 0;
		while (key[j][k] && key[j][k] != '=')
			k++;
		sh->env[i].key = ft_strndup(key[j], k);
		sh->env[i].value = ft_strdup(key[j] + k + 1);
		i++;
		j++;
	}
}

void		builtin_unset(t_sh *sh, char **key, size_t i, size_t j)
{
	int			tmp;
	t_strhash	buf;

	while (key[++j])
	{
		tmp = -1;
		i = 0;
		while (sh->env[i].key)
		{
			if (!ft_strcmp(sh->env[i].key, key[j]))
			{
				ft_strdel(&sh->env[i].key);
				ft_strdel(&sh->env[i].value);
				tmp = i;
			}
			i++;
		}
		i--;
		if (tmp != -1 && tmp != (int)i)
		{
			buf = sh->env[tmp];
			sh->env[tmp] = sh->env[i];
			sh->env[i] = buf;
		}
	}
}

void		builtin_echo(char **cmd)
{
	size_t i;

	i = 1;
	if (!ft_strncmp(cmd[1], "-n", 3))
		i++;
	while (cmd[i])
	{
		ft_dprintf(1, "%s", cmd[i]);
		i++;
		if (cmd[i])
			write(1, " ", 1);
	}
	if (ft_strncmp(cmd[1], "-n", 3))
		write(1, "\n", 1);
}

void		builtin_cd(t_sh *sh, char *path)
{
	char str[1024];
	char *old_pwd;

	if (path == NULL)
		path = ft_get_hash_value(sh->env, "HOME");
	old_pwd = ft_strdup(ft_get_hash_value(sh->env, "OLDPWD"));
	change_value(sh->env, "OLDPWD", getcwd(str, 1024));
	if (chdir(path) == -1)
	{
		ft_dprintf(2, "%s\n", strerror(errno));
		change_value(sh->env, "OLDPWD", old_pwd);
	}
	else
		change_value(sh->env, "PWD", getcwd(str, 1024));
	ft_strdel(&old_pwd);
}
