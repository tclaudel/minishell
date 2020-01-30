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

void	builtin_echo(char **cmd)
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

void	builtin_cd(t_sh *sh, char *path)
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
