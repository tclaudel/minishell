#include "minishell.h"

static void		change_folders(t_sh *sh, char *path)
{
	char		str[1024];
	static char	*old_pwd = NULL;

	if (sh->env->search(sh->env, "OLDPWD"))
	{
		old_pwd = ft_strdup(sh->env->search(sh->env, "OLDPWD"));
		sh->env->change(sh->env, "OLDPWD", getcwd(str, 1024), "string");
	}
	else
		old_pwd = ft_strdup("");
	if (chdir(path) == -1)
	{
		ft_dprintf(2, "%s\n", strerror(errno));
		sh->env->change(sh->env, "OLDPWD", old_pwd, "string");
		sh->question_mark = 1;
	}
	else
	{
		if (sh->env->find(sh->env, "PWD"))
			sh->env->change(sh->env, "PWD", getcwd(str, 1024), "string");
		sh->question_mark = 0;
	}
	ft_strdel(&old_pwd);
}

void			builtin_cd(t_sh *sh, char **cmd)
{
	short			i;
	static char		*path = NULL;

	i = 1;
	if (cmd[i] && (!ft_strcmp(cmd[i], "-L") || !ft_strcmp(cmd[i], "-P")))
		i = 2;
	if (cmd[i] == NULL)
	{
		if (sh->env->search(sh->env, "HOME"))
			path = ft_strdup(sh->env->search(sh->env, "HOME"));
	}
	else
		path = ft_strdup(cmd[i]);
	change_folders(sh, path);
	ft_strdel(&path);
}
