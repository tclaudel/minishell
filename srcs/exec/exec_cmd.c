#include "minishell.h"

static void	search_path(t_sh *sh, char **cmd, char **env)
{
	size_t	i;
	char	*current_cmd;

	i = 0;
	if (execve(cmd[0], cmd, env) == -1)
	{
		current_cmd = ft_strfjoin("/", cmd[0], 2);
		while (sh->path[i])
		{
			cmd[0] = ft_strfjoin(sh->path[i], current_cmd, 0);
			if (execve(cmd[0], cmd, env) != -1)
				exit(EXIT_SUCCESS);
			i++;
			ft_strdel(&cmd[0]);
		}
		if (errno == ENOENT)
			ft_dprintf(2, "minishell: %s: command not found\n", current_cmd);
		else
			ft_dprintf(2, "%s\n", strerror(errno));
		ft_strdel(&current_cmd);
		exit(EXIT_FAILURE);
	}
}

void		exec_builtin(t_sh *sh, size_t j)
{
	if (!ft_strncmp(sh->cmd[j][0], "cd", 3))
		builtin_cd(sh, sh->cmd[j][1]);
	else if (!ft_strncmp(sh->cmd[j][0], "pwd", 4))
		ft_dprintf(1, "%s\n", ft_get_hash_value(sh->env, "PWD"));
	else if (!ft_strncmp(sh->cmd[j][0], "env", 4))
		builtin_env(sh);
	else if (!ft_strncmp(sh->cmd[j][0], "echo", 5))
		builtin_echo(sh->cmd[j]);
	else if (!ft_strncmp(sh->cmd[j][0], "exit", 5))
	{
		ft_dprintf(1, "%s\n", "exit");
		ft_free_tab(sh->path);
		exit(EXIT_SUCCESS);
	}
}

int			exec_cmd(t_sh *sh, char **cmd, char **env)
{
	pid_t	pid;
	int		status;

	(void)env;
	status = 0;
	pid = 0;
	if ((pid = fork()) == -1)
		ft_dprintf(2, "%s\n", strerror(errno));
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
		search_path(sh, cmd, NULL);
	return (1);
}
