#include "minishell.h"
char		*complete_cmd(char *s, char c, size_t i)
{
	char	*complement;

	while(!ft_strchr(s + i + 1, c))
	{
		ft_printf(""YELLOW_BOLD"> "RESET"");
		get_next_line(0, &complement);
		s = ft_strfjoin(s, complement, 3);
	}
	return (s);
}
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
			if (!ft_strchr(s + i + 1, '\"'))
				s = complete_cmd(s , '\"', i);
			i += (size_t)(ft_strchr(s + i + 1, '\"') - (s + i + 1) + 2);
		}
		else if (s[i] == '\'')
		{
			block++;
			// if (!ft_strchr(s + i + 1, '\''))
			// 	s = complete_cmd(s, '\'');
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
	cmd = fill_cmd(s, cmd, 0, 0);
	for (size_t i = 0 ; i < nb; i++)
		dprintf(1, "cmd[%zu]\t: %s\n", i, cmd[i]);
	return (cmd);
} 