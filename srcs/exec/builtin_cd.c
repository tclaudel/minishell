#include "minishell.h"

static void		change_folders(t_sh *sh, char *path)
{
	char		str[1024];
	static char	*old_pwd = NULL;

	if (ft_get_hash_value(sh->env, "OLDPWD"))
	{
		old_pwd = ft_strdup(ft_get_hash_value(sh->env, "OLDPWD"));
		change_value(sh->env, "OLDPWD", getcwd(str, 1024));
	}
	if (chdir(path) == -1)
	{
		ft_dprintf(2, "%s\n", strerror(errno));
		change_value(sh->env, "OLDPWD", old_pwd);
		sh->question_mark = 1;
	}
	else
	{
		change_value(sh->env, "PWD", getcwd(str, 1024));
		sh->question_mark = 0;
	}
	ft_strdel(&old_pwd);
}

void			builtin_cd(t_sh *sh, char **cmd)
{
	short		i;
	char		*path;

	i = 1;
	if (cmd[i] && (!ft_strcmp(cmd[i], "-L") || !ft_strcmp(cmd[i], "-P")))
		i = 2;
	if (cmd[i] == NULL)
		path = ft_strdup(ft_get_hash_value(sh->env, "HOME"));
	else
		path = ft_strdup(cmd[i]);
	change_folders(sh, path);
	ft_strdel(&path);
}
