#include "minishell.h"

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

void			replace_question_mark(char **cmd)
{
	size_t		i;

	i = 0;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "$?"))
		{
			ft_strdel(&cmd[i]);
			cmd[i] = ft_itoa(get_sh_info()->question_mark);
		}
		i++;
	}
}

void			main_loop(t_sh *sh, char *buf)
{
	size_t	i;

	i = 0;
	parsing(sh, buf);
	sh->signal_applied = 0;
	while (sh->cmd[i])
	{
		if (sh->cmd[i][0])
		{
			replace_question_mark(sh->cmd[i]);
			if (sh->cmd[i] && is_builtin(sh->cmd[i][0]))
				exec_builtin(sh, i);
			else if (sh->cmd[i])
				ft_fork_process(sh, sh->cmd[i]);
		}
		i++;
	}
	free_commands(sh);
	print_prompt(sh->env);
}

t_sh			*get_sh_info(void)
{
	static t_sh	sh = {NULL, NULL, NULL, NULL, NULL, 0, NULL, 0, NULL};

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
