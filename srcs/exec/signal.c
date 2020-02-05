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
		else if (sig == SIGINT)
		{
			ft_printf("\n");
			print_prompt(get_sh_info()->env);
		}
	}
}
