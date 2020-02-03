#include "minishell.h"

static char		***alloc_commands(char *str, char c)
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

char		**parse(char *s, char *tmp)
{
	char		*cmd[1024];
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	dprintf(1, "entries\t: %s\n", s);
	tmp = ft_strtrim(s, " \n\t");
	free (s);
	while (s[i])
	{
		
	}
	cmd[j] = NULL;
	
	


	return (cmd);
}

void		parsing(t_sh *sh, char *str)
{
	size_t	i;
	size_t	j;
	char	**entries;

	i = 0;
	j = 0;
	sh->cmd = alloc_commands(str, ';');
	entries = ft_split(str, ';');
	while (entries[j])
	{
		sh->cmd[j] = ft_split(entries[j], ' ');
		j++;
	}
	ft_free_tab(entries);
	ft_strdel(&str);
}
