#include "minishell.h"

void	cd(char *path)
{
	if (chdir(path) == -1)
		perror("cd");
}

int	exec_cmd(t_sh *sh, char **cmd, char **env)
{
	pid_t	pid;
	size_t	i;
	char	*current_cmd;
	int		status;

	status = 0;
	pid = 0;
	i = 0;
	if ((pid = fork()) == -1)
		perror("fork");
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
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
	return (1);
}