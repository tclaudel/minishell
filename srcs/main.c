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
			cmd[i] = ft_itoa(sh()->question_mark);
		}
		i++;
	}
}

void			main_loop(char *buf, size_t i)
{
	parsing(sh(), buf);
	while (sh()->cmd[i])
	{
		if (ft_strchr(sh()->pipes, '|') &&
			sh()->cmd[i][0] && sh()->cmd[i + 1])
			ft_pipe(&i);
		else
			ft_exec(i);
		i++;
	}
	free_commands(sh());
	print_prompt(sh()->env);
}

t_sh			*sh(void)
{
	static t_sh	sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, NULL, {0}, 0};

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
		main_loop(buf, 0);
		ft_strdel(&sh()->pipes);
	}
	ft_dprintf(1, "%s\n", "exit");
	if (sh()->path)
		ft_free_tab(sh()->path);
	return (1);
}
