#include "minishell.h"

static void		wrap_openning_fd(int fd, int saved, int *i)
{
	if (!(fd = open(sh()->cmd[(*i)][0], sh()->redir[(*i)] == 'd' ?
		O_CREAT : O_CREAT | O_TRUNC, 0644)))
		ft_exit(EXIT_FAILURE, *i);
	close(fd);
	if (sh()->cmd[*i][1])
		sh()->cmd[saved] = ft_tabjoin(sh()->cmd[saved], sh()->cmd[*i] + 1);
	(*i)++;
}

void			right_redir(int *i)
{
	int fd;
	int	saved;

	fd = 0;
	saved = (*i)++;
	while (sh()->redir[(*i)] == '>' || sh()->redir[(*i)] == 'd')
		wrap_openning_fd(fd, saved, i);
	if (sh()->cmd[*i][1])
		sh()->cmd[saved] = ft_tabjoin(sh()->cmd[saved], sh()->cmd[*i] + 1);
	if (!(fd = open(sh()->cmd[(*i)][0], sh()->redir[(*i) - 1] == 'd' ?
		O_RDWR | O_CREAT | O_APPEND : O_RDWR | O_CREAT | O_TRUNC, 0644)))
		ft_exit(EXIT_FAILURE, *i);
	if (sh()->redir[(*i)] == '<')
		left_redir(i);
	if (dup2(fd, STDOUT_FILENO) < 1)
		ft_exit(EXIT_FAILURE, *i);
	sh()->fd[1] = fd;
	redirect(sh()->fd[1], 1);
	(*i)++;
	ft_exec(saved);
}
