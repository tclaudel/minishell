#include "minishell.h"

void		handle_sigint(int sig)
{
	if (sig == SIGINT)
		exit(1);
}
