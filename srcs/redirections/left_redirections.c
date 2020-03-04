#include "minishell.h"

void		left_redir(int *i)
{
	int		fd;
	int		saved;

	saved = (*i)++;
	sh()->stdin_bkp = dup(STDIN_FILENO);
	while (sh()->redir[(*i)] == '<')
	{
		dprintf(1, "opening\t: %s\n", sh()->cmd[(*i)][0]);
		if ((fd = open(sh()->cmd[(*i)][0], O_RDONLY)) == -1)
			ft_exit(EXIT_FAILURE);
		close(fd);
		(*i)++;
	}
	if ((fd = open(sh()->cmd[(*i)][0], O_RDONLY)) == -1)
		ft_exit(EXIT_FAILURE);
	if (dup2(fd, STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(fd);
	dup2(STDIN_FILENO, sh()->stdin_bkp);
	close(sh()->stdin_bkp);
	if (sh()->redir[(*i)] && (sh()->redir[(*i)] == '>' ||
		sh()->redir[(*i)] == 'd'))
		right_redir(i);
	ft_exec(saved);
}
