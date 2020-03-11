#include "minishell.h"

static void			search_pwd(t_sh *sh)
{
	char			str[1024];

	if (sh->env)
		sh->env->change(sh->env, "PWD", getcwd(str, 1024), "string");
	if (sh->env && !sh->env->find(sh->env, "PWD"))
	{
		sh->add->new("PWD", getcwd(str, 1024), "string");
		sh->env->add_back(&sh->env, sh->add);
	}
}

static void			change_shlvl(t_sh *sh)
{
	char		*nbr;
	t_hash		*tmp;

	nbr = 0;
	tmp = sh->hash->find(sh->env, "SHLVL");
	if (tmp)
		nbr = ft_itoa(ft_atoi((char *)tmp->value) + 1);
	if (sh->env)
		sh->env->change(sh->env, "SHLVL", nbr, "string");
	else
		sh->env = sh->hash->new("SHLVL", "1", "string");
	ft_strdel(&nbr);
}

void				get_env_var(t_sh *sh, char **env)
{
	size_t		i;
	static char	*token[2] = {0};

	i = 1;
	sh->hash = ft_hash_init();
	if (env[0])
	{
		token[0] = ft_strtok(env[0], "=");
		token[1] = ft_strtok(NULL, "=");
		if (!token[1])
			token[1] = "";
		sh->env = sh->hash->new(token[0], token[1], "string");
		while (env[i])
		{
			token[0] = ft_strtok(env[i], "=");
			token[1] = ft_strtok(NULL, "=");
			if (!token[1])
				token[1] = "";
			sh->add = sh->hash->new(token[0], token[1], "string");
			sh->env->add_back(&sh->env, sh->add);
			i++;
		}
	change_sh_path(sh->env, sh->hash);
	}
	change_shlvl(sh);
	search_pwd(sh);
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
