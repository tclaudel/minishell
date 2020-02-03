#include "minishell.h"

static void		free_commands(t_sh *sh)
{
	size_t i;

	i = 0;
	while (sh->cmd[i])
	{
		//ft_free_tab(sh->cmd[i]);
		i++;
	}
	free(sh->cmd);
}

int				is_builtin(char *cmd)
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

void			main_loop(t_sh *sh, char *buf)
{
	size_t	i;

	i = 0;
	parsing(sh, buf);
	sh->signal_applied = 0;
	while (sh->cmd[i])
	{
		if (sh->cmd[i] && is_builtin(sh->cmd[i][0]))
			exec_builtin(sh, i);
		else if (sh->cmd[i])
			ft_fork_process(sh, sh->cmd[i]);
		i++;
	}
	free_commands(sh);
	print_prompt(sh->env);
}

t_sh			*get_sh_info(void)
{
	static t_sh	sh = {NULL, NULL, NULL, NULL, NULL, 0};

	return (&sh);
}

int				main(int ac, char **av, char **env)
{
	t_sh	*sh;
	char	*buf;

	(void)av[ac];
	printf_welcome();
	sh = get_sh_info();
	get_env_var(sh, env);
	print_prompt(sh->env);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);
	while (get_next_line(0, &buf) > 0)
		main_loop(sh, buf);
	ft_dprintf(1, "%s\n", "exit");
	ft_free_tab(sh->path);
	exit(EXIT_SUCCESS);
	return (1);
}
