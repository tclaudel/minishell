#include "minishell.h"

void		left_redir(int *i)
{
	int		fd;

	if ((fd = open(sh()->cmd[(*i) + 1][0], O_RDONLY)) == -1)
	{
		ft_dprintf(2, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	sh()->stdin_bkp = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(fd);
	dup2(STDIN_FILENO, sh()->stdin_bkp);
	close(sh()->stdin_bkp);
	if (sh()->redir[(*i) + 1] && (sh()->redir[(*i) + 1] == '>' ||
		sh()->redir[(*i) + 1] == 'd'))
		left_redir(i);
	ft_exec(*i);
}
