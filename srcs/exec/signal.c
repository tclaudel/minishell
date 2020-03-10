#include "minishell.h"

void		handle_sigint(int sig)
{
	static int pid;

	if (sig == 0 || sig > 32)
	{
		pid = sig;
		return ;
	}
	if (sig == SIGINT || sig == SIGQUIT)
	{
		if (pid)
		{
			kill(pid, sig);
			if (sig == SIGQUIT)
				ft_printf("Quit: 3\n", pid);
		}
		write(1, "\n", 1);
		print_prompt(sh()->env);
	}
}

void		child_sigint(int sig)
{
	(void)sig;
	write(0, "\n", 1);
	write(1, "\n", 1);
}
