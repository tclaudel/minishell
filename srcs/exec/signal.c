#include "minishell.h"

void		children_slained(int sig)
{
	if (SIGKILL == sig);
		dprintf(1, "a child as been slained");
}

void		handle_sigint(int sig)
{
	static int		pid;

	if (sig == 0 || sig > 32)
	{
		pid = sig;
		return ;
	}
	signal(SIGKILL, children_slained);
	if ((sig == SIGINT || sig == SIGQUIT))
	{
		if (pid)
		{
			kill(pid, sig);
			if (sig == SIGINT)
				ft_printf("\n");
			if (sig == SIGQUIT)
				ft_printf("\n[1]\t%d quit\n", pid);
			return ;
		}
		else 
		{
			ft_printf("\n");
			print_prompt(get_sh_info()->env);
		}
	}
}
