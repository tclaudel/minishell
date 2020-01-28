
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <signal.h>
# include <unistd.h>


typedef struct		s_sh
{
	char	**cmd;
}					t_sh;

void				parsing(t_sh *sh, char *str);
void				exec_cmd(char **cmd);
void				cd(char *path);

#endif
