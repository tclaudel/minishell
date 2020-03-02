#include "minishell.h"

void		left_redir(int *i)
{
	int		fd;

	dprintf(1, "opening\t: %s\n", sh()->cmd[(*i) + 1][0]);
	if ((fd = open(sh()->cmd[(*i) + 1][0], O_RDONLY)) == -1)
		exit(EXIT_FAILURE);
	sh()->stdin_bkp = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(fd);
	dup2(STDIN_FILENO, sh()->stdin_bkp);
	close(sh()->stdin_bkp);
	ft_display_tab(sh()->cmd[*i], "executing");
	ft_exec(*i);
}
