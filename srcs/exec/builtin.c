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
	sh->question_mark = 0;
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
		if (tmp != -1 && tmp != (int)i - 1)
		{
			buf = sh->env[tmp];
			sh->env[tmp] = sh->env[i - 1];
			sh->env[i - 1] = buf;
		}
	}
	if (sh->path)
	{
		ft_free_tab(sh->path);
		if (ft_get_hash_value(sh->env, "PATH"))
			sh->path = ft_split(ft_get_hash_value(sh->env, "PATH"), ':');
		else
			sh->path = ft_calloc(sizeof(char *), 1);
	}
	sh->question_mark = 0;
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
	get_sh_info()->question_mark = 0;
}
