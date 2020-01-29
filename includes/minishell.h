
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <dirent.h>

typedef struct		s_sh
{
	char		cd;
	char		**key;
	char		**value;
	char		***cmd;
	char		**path;
	t_strhash	*env;
}					t_sh;

void				parsing(t_sh *sh, char *str);
int					exec_cmd(t_sh *sh, char **cmd, char **env);
void				builtin_env(t_sh *sh);
void				cd(t_sh *sh, char *path);

#endif
