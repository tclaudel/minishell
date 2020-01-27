
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>

void				parsing(char *str);

typedef struct		s_sh
{
	char	**cmd;
}					t_sh;

#endif
