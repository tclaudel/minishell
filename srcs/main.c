
#include "minishell.h"

int		main(void)
{
	char *buf;

	ft_dprintf(1, "minishell $> ");
	while (get_next_line(0, &buf) > 0)
	{
		parsing(buf);
		ft_dprintf(1, "%s\n", buf);
		ft_dprintf(1, "minishell $> ");
	}
	return (1);
}
