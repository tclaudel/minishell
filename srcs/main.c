
#include "minishell.h"

int		get_env_var(t_sh *sh, char **env)
{
	size_t i;
	size_t j;

	i = 0;
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
		return (0);
	}
	exit(EXIT_FAILURE);
}

int		main(int ac, char **av, char **env)
{
	t_sh	*sh;
	char	*buf;

	(void)av[ac];
	sh = malloc(sizeof(t_sh));
	get_env_var(sh, env);
	sh->env = ft_strhash(sh->key, sh->value);
	sh->path = ft_split(ft_get_hash_value(sh->env, "PATH"), ':');
	// ft_dprintf(2, "\033[34;01m%s\033[00m\n", ft_get_hash_value(sh->env, "PATH"));
	ft_dprintf(1, "minishell $> ");
	while (get_next_line(0, &buf) > 0)
	{
		// sh->cd = 0;
		parsing(sh, buf);
		ft_strdel(&buf);
		if (sh->cmd[0])
			exec_cmd(sh, sh->cmd, env);
		ft_free_tab(sh->cmd);
		ft_dprintf(1, "minishell $> ");
	}
	return (1);
}
