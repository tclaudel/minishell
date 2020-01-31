
#include "minishell.h"

void		print_prompt(t_strhash *hash)
{
	if (ft_get_hash_value(hash, "PWD"))
	{
		ft_dprintf(1, ""YELLOW_BOLD "%s: %s $> " RESET"",
			ft_get_hash_value(hash, "USER"),
			ft_strrchr(ft_get_hash_value(hash, "PWD"), '/'));
	}
	else
		ft_dprintf(1, ""YELLOW_BOLD "%s: %s $> " RESET"",
			ft_get_hash_value(hash, "USER"), NULL);
}

static void		free_commands(t_sh *sh)
{
	size_t i;

	i = 0;
	while (sh->cmd[i])
	{
		ft_free_tab(sh->cmd[i]);
		i++;
	}
	free(sh->cmd);
}

int		is_builtin(char *cmd)
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

void			get_entry(t_sh *sh, char *buf, char **env)
{
	size_t	i;

	i = 0;
	parsing(sh, buf);
	while (sh->cmd[i])
	{
		if (sh->cmd[i] && is_builtin(sh->cmd[i][0]))
			exec_builtin(sh, i);
		else if (sh->cmd[i])
			ft_fork_process(sh, sh->cmd[i], env);
		i++;
	}
	free_commands(sh);
	print_prompt(sh->env);
}

t_sh	*get_sh_info(void)
{
	static t_sh	sh = {NULL,NULL,NULL,NULL,NULL};

	return (&sh);
}

int				main(int ac, char **av, char **env)
{
	t_sh	*sh;
	char	*buf;

	(void)av[ac];
	sh = get_sh_info();
	get_env_var(sh, env);
	print_prompt(sh->env);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);
	while (get_next_line(0, &buf) > 0)
		get_entry(sh, buf, env);
	ft_dprintf(1, "%s\n", "exit");
	ft_free_tab(sh->path);
	exit(EXIT_SUCCESS);
	return (1);
}
