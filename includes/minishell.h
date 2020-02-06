
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
	char		signal_applied;
}					t_sh;

void				parsing(t_sh *sh, char *str);
void				exec_cmd(t_sh *sh, char **cmd);
void				builtin_env(t_sh *sh);
void				exec_builtin(t_sh *sh, size_t j);
void				builtin_cd(t_sh *sh, char *path);
int					get_env_var(t_sh *sh, char **env);
void				builtin_echo(char **cmd);
void				builtin_unset(t_sh *sh, char **key, size_t i, size_t j);
void				builtin_export(t_sh *sh, char **key);
void				handle_sigint(int sig);
int					is_builtin(char *cmd);
int					ft_fork_process(t_sh *sh, char **cmd);
void				print_prompt(t_strhash *hash);
t_strhash			*realloc_hash(t_strhash *hash, size_t size);
t_sh				*get_sh_info(void);
void				printf_welcome(void);
void				print_prompt(t_strhash *hash);
char				***alloc_commands(char *str, size_t *nb);
size_t				bloc_counter(char *s, size_t i, size_t block);
char				**parse(char *s);
char				**fill_cmd(char *s, char **cmd, size_t i, size_t j);
char				*double_quote_allocator(char *s, size_t *j);
char				*simple_quote_allocator(char *s, size_t *j);
char				*non_special_allocator(char *s, size_t *j);
char				*quote_checker(char *s, size_t quote, size_t dquote);
size_t				separator_counter(char *s, size_t i, size_t block);

#endif
