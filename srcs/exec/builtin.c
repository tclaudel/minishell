#include "minishell.h"

int			is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") ||
	!ft_strcmp(cmd, "env") ||
	!ft_strcmp(cmd, "pwd") ||
	!ft_strcmp(cmd, "exit") ||
	!ft_strcmp(cmd, "echo") ||
	!ft_strcmp(cmd, "unset") ||
	!ft_strcmp(cmd, "export"))
		return (1);
	return (0);
}

void		builtin_env(t_sh *sh, t_hash *env)
{
	if (env)
		env->change(env, "_", "env", "string");
	while (env)
	{
		ft_dprintf(1, "%s", env->key);
		ft_dprintf(1, "%s", "=");
		ft_dprintf(1, "%s\n", env->value);
		env = env->next;
	}
	sh->question_mark = 0;
}

void		change_sh_path(t_hash *env, t_hash *hash)
{
	if (sh()->path)
		ft_free_tab(sh()->path);
	if (hash->search(env, "PATH"))
		sh()->path = ft_split(env->search(env, "PATH"), ':');
	else
		sh()->path = ft_calloc(sizeof(char *), 1);
	sh()->question_mark = 0;
}

void		builtin_unset(t_sh *sh, char **key, size_t j)
{
	while (key[++j])
	{
		if (sh->env->search(sh->env, key[j]))
		{
			sh->env = sh->env->find(sh->env, key[j]);
			sh->env->del(&sh->env, sh->env->before, sh->env->next);
		}
	}
	change_sh_path(sh->env, sh->hash);
}

void		builtin_echo(char **cmd)
{
	size_t i;

	i = 1;
	if (!cmd[1])
	{
		write(1, "\n", 1);
		return ;
	}
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
	sh()->question_mark = 0;
}
