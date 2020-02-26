#include "minishell.h"

static void		free_commands(void)
{
	size_t i;

	i = 0;
	while (sh()->cmd[i])
	{
		ft_free_tab(sh()->cmd[i]);
		i++;
	}
	free(sh()->cmd);
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
			cmd[i] = ft_itoa(sh()->question_mark);
		}
		i++;
	}
}

void			main_loop(char *buf)
{
	parsing(sh(), buf);
	if (sh()->pipes[0] != 0)
		redirections();
	else
		ft_exec(0);
	free_commands();
	print_prompt(sh()->env);
}

t_sh			*sh(void)
{
	static t_sh	sh = {0};

	return (&sh);
}

int				main(int ac, char **av, char **env)
{
	char	*buf;
	t_hash	*top;

	(void)av[ac];
	printf_welcome();
	get_env_var(sh(), env);
	print_prompt(sh()->env);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);
	while (get_next_line(0, &buf) > 0)
	{
		top = sh()->env->top;
		while (sh()->env)
		{
			//ft_dprintf(1, "%-40s=%-60sadress:%p\ttop:%p\tbefore:%p\tnext:%p\n\n", sh()->env->key, sh()->env->value, sh()->env, sh()->env->top, sh()->env->before, sh()->env->next);
			sh()->env = sh()->env->next;
		}
		sh()->env = top;
		main_loop(buf);
		ft_strdel(&sh()->pipes);
	}
	ft_dprintf(1, "%s\n", "exit");
	if (sh()->path)
		ft_free_tab(sh()->path);
	return (1);
}
