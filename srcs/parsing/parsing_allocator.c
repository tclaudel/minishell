#include "minishell.h"

char		*complete_cmd(char *s, char c)
{
	char	*str;
	char	buff[1024];
	int		ret;

	str = ft_strdup("");
	ft_printf(""YELLOW_BOLD"> "RESET"");
	while ((ret = read(0, buff, 1023)))
	{
		if (ret < 0)
			return (NULL);
		buff[ret] = 0;
		str = ft_strfjoin(str, buff, 1);
		if (ft_strchr(str, c))
			break ;
		ft_printf(""YELLOW_BOLD"> "RESET"");
	}
	s = ft_strfjoin(s, str, 2);
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

size_t		bloc_counter(char *s, size_t i, size_t block)
{
	while (s[i] && s[i] != '\n')
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
		else if (s[i] && !ft_strchr(" \t\'\"", s[i]))
		{
			block++;
			while (s[i] && !ft_strchr(" \t\'\"", s[i]))
				i++;
		}
	}
	return (block);
}

char		*quote_checker(char *s)
{
	size_t	i;
	size_t	quote;
	size_t	dquote;
	char	*dest;

	i = 0;
	quote = 0;
	dquote = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			quote++;
		if (s[i] == '\"')
			dquote++;
		i++;
	}
	if (dquote % 2)
		dest = complete_cmd(s, '\"');
	else if (quote % 2)
		dest = complete_cmd(s, '\'');
	else
		dest = s;
	return (dest);
}

char		**parse(char *s)
{
	size_t			nb;
	char			**cmd;

	s = quote_checker(s);
	nb = bloc_counter(s, 0, 0);
	cmd = (char **)malloc(sizeof(char *) * (nb + 1));
	cmd[nb] = NULL;
	cmd = fill_cmd(s, cmd, 0, 0);
	ft_display_tab(cmd, "cmd");
	return (cmd);
}
