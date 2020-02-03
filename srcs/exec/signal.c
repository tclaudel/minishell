#include "minishell.h"

void		handle_sigint(int sig)
{
	static int		pid;

	if (sig == 0 || sig > 32)
	{
		pid = sig;
		return ;
	}
	if ((sig == SIGINT || sig == SIGQUIT))
	{
		if ((kill(pid, sig) == 0))
		{
			if (sig == SIGINT)
				ft_printf("\n");
			if (sig == SIGQUIT)
				ft_printf("\n[1]\t%d quit\n", pid);
		}
		else
		{
			ft_printf("\n");
			print_prompt(get_sh_info()->env);
		}
	}
}
