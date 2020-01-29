#include "minishell.h"

void	cd(t_sh *sh, char *path)
{
	char *str;

	str = malloc(1024);
	if (chdir(path) == -1)
		perror("cd");
	change_value(sh->env, "PWD", getcwd(str, 1024));
}

static int	search_path(t_sh *sh, char **cmd, char **env)
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
				return (0);
			i++;
			ft_strdel(&cmd[0]);
		}
		perror("shell");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int			exec_cmd(t_sh *sh, char **cmd, char **env)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = 0;
	if ((pid = fork()) == -1)
		perror("fork");
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
		search_path(sh, cmd, env);
	return (1);
}
