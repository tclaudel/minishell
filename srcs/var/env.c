#include "minishell.h"

static void			search_pwd(t_sh *sh)
{
	char			str[1024];

	sh->env->change(sh->env, "PWD", getcwd(str, 1024), "string");
}

void			get_env_var(t_sh *sh, char **env)
{
	size_t	i;

	i = 1;
	sh->hash = ft_hash_init();
	sh->env = sh->hash->new(ft_strtok(env[0], "="),
	ft_strtok(NULL, "="), "string");
	while (env[i])
	{
		sh->add = sh->hash->new(ft_strtok(env[i], "="),
		ft_strtok(NULL, "="), "string");
		sh->env->add_back(&sh->env, sh->add);
		i++;
	}
	sh->path = ft_split(sh->env->search(sh->env, "PATH"), ':');
	search_pwd(sh);
}
<<<<<<< HEAD

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
			if (sh->env->search(sh->env, buf + 1))
				cmd[i] = ft_strdup(sh->env->search(sh->env, buf + 1));
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
=======
>>>>>>> master
