
#include "minishell.h"

// void	exec_cmd(char **cmd)
// {
// 	pid_t	pid;
// 	int		status;

// 	status = 0;
// 	pid = 0;
// 	if ((pid = fork()) == -1)
// 		perror("fork");
// 	if (pid > 0)
// 	{
// 		waitpid(pid, &status, 0);
// 		kill(pid, SIGTERM);
// 	}
// 	else
// 	{
// 		if (execve(cmd[0], cmd, NULL) == -1)
// 		{
// 			perror("shell");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// }

int		main(void)
{
	t_sh	*sh;
	char	*buf;

	sh = malloc(sizeof(t_sh));
	ft_dprintf(1, "minishell $> ");
	while (get_next_line(0, &buf) > 0)
	{
		parsing(sh, buf);
		if (sh->cmd[0])
			exec_cmd(sh->cmd);
		ft_dprintf(1, "minishell $> ");
	}
	ft_dprintf(1, "Euuuh ... Nique ta mere !\n");
	return (1);
}
