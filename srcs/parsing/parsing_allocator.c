#include "minishell.h"

char		***alloc_commands(char *str, char c)
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

size_t	bloc_counter(char *s, size_t i, size_t block)
{
	while (s[i])
	{
		if (s[i] == ' ')
		{
			while (s[i] && s[i] == ' ')
				i++;
		}
		else if (s[i] == '\"')
		{
			block++;
			i += (size_t)(ft_strchr(s + i + 1, '\"') - (s + i + 1) + 2);
		}
		else if (s[i] == '\'')
		{
			block++;
			i += (size_t)(ft_strchr(s + i + 1, '\'') - (s + i + 1) + 2);
		}
		else if (s[i] && !ft_strchr(" \t\n\'\"", s[i]))
		{
			block++;
			while (s[i] && !ft_strchr(" \t\n\'\"", s[i]))
				i++;
		}
	}
	return (block);
}

char			**parse(char *s)
{
	size_t			nb;
	char			**cmd;


	nb = bloc_counter(s, 0, 0);
	cmd = (char **)malloc(sizeof(char *) * (nb + 1));
	cmd[nb] = NULL;
	cmd = fill_cmd(s, nb, cmd, 0);
	for (size_t i = 0 ; i < nb; i++)
		dprintf(1, "cmd[%zu]\t: %s\n", i, cmd[i]);
	return (cmd);
}