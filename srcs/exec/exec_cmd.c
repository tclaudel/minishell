#include "minishell.h"

void		exec_builtin(t_sh *sh, size_t j)
{
	char str[1024];

	if (!ft_strncmp(sh->cmd[j][0], "cd", 3))
		builtin_cd(sh, sh->cmd[j]);
	else if (!ft_strncmp(sh->cmd[j][0], "pwd", 4))
	{
		ft_dprintf(1, "%s\n", getcwd(str, 1024));
		sh->question_mark = 0;
	}
	else if (!ft_strncmp(sh->cmd[j][0], "env", 4))
		builtin_env(sh, sh->env);
	else if (!ft_strncmp(sh->cmd[j][0], "echo", 5))
		builtin_echo(sh->cmd[j]);
	else if (!ft_strncmp(sh->cmd[j][0], "unset", 5))
		builtin_unset(sh, sh->cmd[j], 0);
	else if (!ft_strncmp(sh->cmd[j][0], "export", 7))
		builtin_export(sh, sh->cmd[j]);
	else if (!ft_strncmp(sh->cmd[j][0], "exit", 5))
	{
		ft_dprintf(1, "%s\n", "exit");
		if (sh->path)
			ft_free_tab(sh->path);
		exit(EXIT_SUCCESS);
	}
}

int			ft_fork_process(t_sh *sh, char **cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = 0;
	if ((pid = fork()) == -1)
		ft_dprintf(2, "%s\n", strerror(errno));
	if (pid > 0)
	{
		handle_sigint(pid);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			sh->question_mark = WTERMSIG(status) + 128;
		else
			sh->question_mark = WEXITSTATUS(status);
		handle_sigint(0);
	}
	else
	{
		exec_cmd(sh, cmd);
	}
	return (1);
}

static char	**cpy_environ(t_hash *env)
{
	size_t	i;
	char	**env_cpy;

	env_cpy = malloc(sizeof(char *) * (env->len(env) + 1));
	i = 0;
	while (env)
	{
		env_cpy[i] = ft_strjoin(env->key, "=");
		env_cpy[i] = ft_strfjoin(env_cpy[i], env->value, 1);
		env = env->next;
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

void		exec_cmd(t_sh *sh, char **cmd)
{
	size_t	i;
	char	*current_cmd;
	char	**env_cpy;

	i = 0;
	env_cpy = cpy_environ(sh->env);
	if (execve(cmd[0], cmd, env_cpy) == -1)
	{
		current_cmd = ft_strfjoin("/", cmd[0], 2);
		while (sh->path && sh->path[i])
		{
			cmd[0] = ft_strfjoin(sh->path[i], current_cmd, 0);
			execve(cmd[0], cmd, env_cpy);
			i++;
			ft_strdel(&cmd[0]);
		}
		if (errno == ENOENT)
			ft_dprintf(2, "minishell: %s: command not found\n", current_cmd);
		else
			ft_dprintf(2, "%s\n", strerror(errno));
		ft_free_tab(env_cpy);
		ft_strdel(&current_cmd);
		exit(127);
	}
}
