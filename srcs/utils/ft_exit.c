#include "minishell.h"

void	ft_exit(int exit_code)
{
	ft_dprintf(2, "%s\n", strerror(errno));
	exit(exit_code);
}
