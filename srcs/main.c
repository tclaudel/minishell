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

void	ft_exec(size_t i)
{
	replace_question_mark(sh()->cmd[i]);
	if (sh()->cmd[i][0] && is_builtin(sh()->cmd[i][0]))
		exec_builtin(sh(), i);
	else if (sh()->cmd[i] && sh()->cmd[i][0])
		ft_fork_process(sh(), sh()->cmd[i]);
}

void	ft_pipe(size_t i)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (pipe(sh()->fd))
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		ft_dprintf(2, "%s\n", strerror(errno));
	if (pid == 0)
	{
		dup2(sh()->fd[1], 1);
		ft_exec(i);
		exit(0);
	}
	dup2(sh()->fd[0], 0);
	close(sh()->fd[1]);
	close(sh()->fd[0]);
	waitpid(-1, &status, 0);
}

// void	ft_pipe(t_file *file, char **args2)
// {
// 	pid_t	pid;
// 	F->stop2 = 0;
// 	pipe(F->pfd);
// 	if ((pid = fork()) == 0)
// 	{
// 		dup2(F->pfd[1], 1);
// 		ft_manager(args2, file);
// 		exit(0);
// 	}
// 	dup2(F->pfd[0], 0);
// 	close(F->pfd[0]);
// 	close(F->pfd[1]);
// 	while (wait(&F->status) > 0)
// 		;
// }

void		main_loop(char *buf, size_t i)
{
	parsing(sh(), buf);
	while (sh()->cmd[i])
	{
		if (ft_strchr(sh()->pipes, '|') &&
			sh()->cmd[i][0] && sh()->cmd[i + 1])
			ft_pipe(i);
		else
		{
			replace_question_mark(sh()->cmd[i]);
			if (sh()->cmd[i][0] && is_builtin(sh()->cmd[i][0]))
				exec_builtin(sh(), i);
			else if (sh()->cmd[i] && sh()->cmd[i][0])
				ft_fork_process(sh(), sh()->cmd[i]);
		}
		i++;
	}
	free_commands(sh());
	print_prompt(sh()->env);
}

t_sh			*sh(void)
{
	static t_sh	sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, NULL, {0}};

	return (&sh);
}

int				main(int ac, char **av, char **env)
{
	char	*buf;

	(void)av[ac];
	printf_welcome();
	get_env_var(sh(), env);
	print_prompt(sh()->env);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);
	while (get_next_line(0, &buf) > 0)
	{
		main_loop(buf, 0);
		ft_strdel(&sh()->pipes);
	}
	ft_dprintf(1, "%s\n", "exit");
	ft_free_tab(sh()->path);
	exit(EXIT_SUCCESS);
	return (1);
}

