
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
# include <errno.h>

typedef struct		s_sh
{
	char		**key;
	char		**value;
	char		***cmd;
	char		**path;
	t_strhash	*env;
}					t_sh;

void				parsing(t_sh *sh, char *str);
void				exec_cmd(t_sh *sh, char **cmd, char **env);
void				builtin_env(t_sh *sh);
void				exec_builtin(t_sh *sh, size_t j);
void				builtin_cd(t_sh *sh, char *path);
int					get_env_var(t_sh *sh, char **env);
void				builtin_echo(char **cmd);
void				builtin_unset(t_sh *sh, char **key, size_t i, size_t j);
void				builtin_export(t_sh *sh, char **key);
void				handle_sigint(int sig);
int					is_builtin(char *cmd);
t_strhash			*realloc_hash(t_strhash *hash, size_t size);
int					ft_fork_process(t_sh *sh, char **cmd, char **env, size_t i);
void				print_prompt(t_strhash *hash);
t_sh				*get_sh_info(void);

#endif
