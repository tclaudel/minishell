#include "minishell.h"

void	parsing(t_sh *sh, char *str)
{
	size_t	i;

	i = 0;
	sh->cmd = ft_split(str, ' ');
	if (sh->cmd[0])
	{
		if (!ft_strncmp(sh->cmd[0], "cd", 3))
		{
			sh->cd = 1;
			cd(sh->cmd[1]);
		}
		else if (!ft_strncmp(sh->cmd[0], "exit", 5))
		{
			ft_dprintf(1, "%s\n", "exit");
			ft_free_tab(sh->cmd);
			exit(EXIT_SUCCESS);
		}
		else
			sh->cmd[0] = ft_strfjoin("/bin/", sh->cmd[0], 2);
	}
}
