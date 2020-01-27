
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <signal.h>


typedef struct		s_sh
{
	char	**cmd;
}					t_sh;

void				parsing(t_sh *sh, char *str);

#endif
