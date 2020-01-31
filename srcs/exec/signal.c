#include "minishell.h"

void		handle_sigint(int sig)
{
	static int  pid;	
	
	if (sig == 0 || sig > 32)
	{
		pid = sig;
		return ;
	}
	if (sig == SIGINT || sig == SIGQUIT)
	{
		if (pid)
		{
			if (sig == SIGINT)
				ft_printf("\n");
			if (sig == SIGQUIT)
				ft_printf("[1]\t%d quit\n", pid);
			kill(pid, sig);
		}
		// else
		// {
		// 	ft_printf("\n");
		// 	print_prompt(get_sh_info()->env);
		// }
	}
}
