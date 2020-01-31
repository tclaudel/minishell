
#include "minishell.h"

static void		print_prompt(t_strhash *hash)
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

static int		is_builtin(char *cmd)
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

static void			handle_sigint(int sig)
{
	if (sig == SIGINT)
		exit(1);
}

int				main(int ac, char **av, char **env)
{
	t_sh	*sh;
	size_t	i;
	char	*buf;

	(void)av[ac];
	sh = malloc(sizeof(t_sh));
	get_env_var(sh, env);
	print_prompt(sh->env);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);
	while (get_next_line(0, &buf) > 0)
	{
		parsing(sh, buf);
		i = 0;
		while (sh->cmd[i])
		{
			if (sh->cmd[i][0] && is_builtin(sh->cmd[i][0]))
				exec_builtin(sh, i);
			else if (sh->cmd[i][0])
				exec_cmd(sh, sh->cmd[i], env);
			i++;
		}
		free_commands(sh);
		print_prompt(sh->env);
	}
	return (1);
}
