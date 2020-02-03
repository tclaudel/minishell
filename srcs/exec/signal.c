#include "minishell.h"

void		handle_sigint(int sig)
{
	static int		pid;
	static char		signal_applied = 0;

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
			signal_applied++;
			if (sig == SIGQUIT)
				ft_printf("\n[1]\t%d quit\n", pid);
		}
		if (!pid && signal_applied == 0)
		{
			ft_printf("\n");
			print_prompt(get_sh_info()->env);
		}
		//dprintf(1, "signal_applied : %d", signal_applied);
	}
}
