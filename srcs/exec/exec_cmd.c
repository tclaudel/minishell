#include "minishell.h"

void	cd(char *path)
{
	if (chdir(path) == -1)
		perror("cd");
}

void	exec_cmd(char **cmd)
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
	{
		if (execve(cmd[0], cmd, NULL) == -1)
		{
			cmd[0] = ft_strfjoin("/usr/", cmd[0], 2);
			if (execve(cmd[0], cmd, NULL) == -1)
				perror("shell");
				exit(EXIT_FAILURE);
		}
	}
}