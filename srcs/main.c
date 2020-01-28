
#include "minishell.h"

int		main(void)
{
	t_sh	*sh;
	char	*buf;

	sh = malloc(sizeof(t_sh));
	ft_dprintf(1, "minishell $> ");
	while (get_next_line(0, &buf) > 0)
	{
		sh->cd = 0;
		parsing(sh, buf);
		ft_strdel(&buf);
		if (sh->cmd[0] && sh->cd == 0)
			exec_cmd(sh->cmd);
		ft_free_tab(sh->cmd);
		ft_dprintf(1, "minishell $> ");
	}
	ft_dprintf(1, "Euuuh ... Nique ta mere !\n");
	return (1);
}
