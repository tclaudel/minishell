#include "minishell.h"

char	***split_commands(char *str, char c)
{
	char		***cmd;
	size_t		i;
	size_t		nb;

	i = 0;
	nb = 1;
	while (str[i])
	{
		if (str[i] == c)
			nb++;
		i++;
	}
	cmd = (char ***)ft_calloc(sizeof(char **), (nb + 1));
	return (cmd);
}

void	parsing(t_sh *sh, char *str)
{
	size_t	i;
	size_t	j;
	char	**entries;

	i = 0;
	j = 0;
	sh->cmd = split_commands(str, ';');
	entries = ft_split(str, ';');
	while (entries[j])
	{
		sh->cmd[j] = ft_split(entries[j], ' ');
		if (sh->cmd[j][0])
		{
			if (!ft_strncmp(sh->cmd[j][0], "cd", 3))
				cd(sh->cmd[j][1]);
			if (!ft_strncmp(sh->cmd[j][0], "env", 4))
				builtin_env(sh);
			else if (!ft_strncmp(sh->cmd[j][0], "exit", 5))
			{
				ft_dprintf(1, "%s\n", "exit");
				// ft_free_tab(sh->cmd[j]);
				ft_free_tab(sh->path);
				exit(EXIT_SUCCESS);
			}
		}
		j++;
	}
}
