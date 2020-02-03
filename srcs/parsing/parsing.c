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

char		*is_a_symbol(char c)
{
	return (ft_strchr(" \t\n\'\"", c));
}

static size_t	bloc_counter(char *s, size_t i)
{
	size_t	block;

	block = 1;
	while (s[i])
	{
		if (s[i] == ' ')
		{
			block++;
			while (s[i] && s[i] != ' ')
				i++;
		}
		else if (s[i] == '\"')
		{
			block++;
			while (s[i] && s[i] != '\"')
				i++;
		}
		else if (s[i] == '\'')
		{
			block++;
			while (s[i] && s[i] != '\'')
				i++;
		}
		i++;
	}
	return (block);
}


void			parse(char *s)
{
	// char			**cmd;
	size_t			nb;

	dprintf(1, "entries\t: %s\n", s);
	nb = bloc_counter(s, 0);
	printf("nb\t: %zu\n", nb);
	//cmd = (char **)malloc(sizeof(char *) * (nb + 1);
	// return (cmd);
}

void			parsing(t_sh *sh, char *str)
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
		parse(entries[j]);
		j++;
	}
	ft_free_tab(entries);
	ft_strdel(&str);
}
