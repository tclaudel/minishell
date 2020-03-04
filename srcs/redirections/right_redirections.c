#include "minishell.h"

void	right_redir(int *i)
{
	int fd;
	int	saved;

	saved = *i;
	(*i)++;
	while (sh()->redir[(*i)] == '>' || sh()->redir[(*i)] == 'd')
	{
		dprintf(1, "creating\t: %s\n", sh()->cmd[(*i)][0]);
		if (!(fd = open(sh()->cmd[(*i)][0], sh()->redir[(*i)] == 'd' ?
			O_CREAT : O_CREAT | O_TRUNC, 0644)))
			exit(EXIT_SUCCESS);
		close(fd);
		if (sh()->cmd[*i][1])
			sh()->cmd[saved] = ft_tabjoin(sh()->cmd[saved], sh()->cmd[*i]);
		(*i)++;
	}
	if (sh()->cmd[*i][1])
		sh()->cmd[saved] = ft_tabjoin(sh()->cmd[saved], sh()->cmd[*i] + 1);
	ft_display_tab(sh()->cmd[saved], "exec");
	dprintf(1, "opening\t: %s\n", sh()->cmd[(*i)][0]);
	if (!(fd = open(sh()->cmd[(*i)][0], sh()->redir[(*i) - 1] == 'd' ?
		O_RDWR | O_CREAT | O_APPEND : O_RDWR | O_CREAT | O_TRUNC, 0644)))
		exit(EXIT_SUCCESS);
	if (dup2(fd, STDOUT_FILENO) < 1)
		exit(EXIT_SUCCESS);
	sh()->fd[1] = fd;
	redirect(sh()->fd[1], 1);
	ft_exec(saved);
}
