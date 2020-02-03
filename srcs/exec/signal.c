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
			get_sh_info()->childrens--;
			if (sig == SIGQUIT)
				ft_printf("\n[1]\t%d quit\n", pid);
		}
		else if (get_sh_info()->childrens == get_sh_info()->oldchilds)
		{
			ft_printf("\n");
			print_prompt(get_sh_info()->env);
		}
	}
}
