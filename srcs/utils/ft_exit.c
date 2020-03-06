#include "minishell.h"

void	ft_exit(int exit_code, int i)
{
	ft_dprintf(2, "minishell: %s: %s\n",
		sh()->cmd[i][0], strerror(errno));
	exit(exit_code);
}
