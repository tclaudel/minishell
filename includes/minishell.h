
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <dirent.h>
# include <string.h>
# include "errno.h"

typedef struct		s_sh
{
	char		**key;
	char		**value;
	char		***cmd;
	char		**path;
	t_strhash	*env;
}					t_sh;

void				parsing(t_sh *sh, char *str);
int					exec_cmd(t_sh *sh, char **cmd, char **env);
void				builtin_env(t_sh *sh);
void				exec_builtin(t_sh *sh, size_t j);
void				builtin_cd(t_sh *sh, char *path);
int					get_env_var(t_sh *sh, char **env);
void				builtin_echo(char **cmd);

#endif
