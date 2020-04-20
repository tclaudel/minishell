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

void			main_loop(char *buf, size_t i)
{
	char	**sep;
	char	*tok;

	tok = 0;
	if (analyser(buf, tok, 0))
	{
		sep = ft_split(buf, ';');
		while (sep[i])
		{
			if (!parsing(sep[i]))
			{
				ft_free_tab(sep);
				return ;
			}
			if (sh()->redir[0] != 0)
				redirections(0, 0);
			else
				ft_exec(0);
			free_commands();
			ft_strdel(&sh()->redir);
			i++;
		}
		free(sep);
	}
}

t_sh			*sh(void)
{
	static t_sh	sh = {0};

	return (&sh);
}

int				main(int ac, char **av, char **env)
{
	char	*buf;

	(void)av[ac];
	// printf_welcome();
	get_env_var(sh(), env, 1);
	print_prompt(sh()->env);
	signal(SIGQUIT, handle_sigint);
	signal(SIGINT, handle_sigint);
	while (get_next_line(0, &buf) > 0)
	{
		main_loop(buf, 0);
		print_prompt(sh()->env);
		ft_strdel(&buf);
	}
	ft_dprintf(1, "%s\n", "exit");
	if (sh()->path)
		ft_free_tab(sh()->path);
	return (1);
}
