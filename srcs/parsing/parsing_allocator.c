#include "minishell.h"

char		*complete_cmd(char *s, char c)
{
	char	*str;
	char	buff[1024];
	int		ret;

	str = ft_strdup("\n");
	ft_printf(""YELLOW_BOLD"> "RESET"");
	while (1)
	{
		ret = read(0, buff, 1023);
		buff[ret] = 0;
		str = ft_strfjoin(str, buff, 1);
		if (ft_strchr(str, c))
			break ;
		if (buff[0] != 0)
			ft_printf(""YELLOW_BOLD"> "RESET"");
	}
	s = ft_strfjoin(s, str, 2);
	return (s);
}

size_t		bloc_counter(char *s, size_t i, size_t block)
{
	while (s[i] && s[i] != '\n')
	{
		if (s[i] == ' ')
		{
			while (s[i] && ft_strchr(WHITESPACES, s[i]))
				i++;
		}
		else if (s[i] == '\"')
		{
			block++;
			quotes_splitter(s, &i, '\"');
		}
		else if (s[i] == '\'')
		{
			block++;
			quotes_splitter(s, &i, '\'');
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

char		*quote_checker(char *s, size_t quote, size_t dquote)
{
	size_t	i;
	char	*dest;
	char	c;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !(dquote % 2))
			quote++;
		if (s[i] == '\"' && !(quote % 2))
			dquote++;
		i++;
	}
	if (dquote % 2)
		dest = complete_cmd(s, '\"');
	else if (quote % 2)
		dest = complete_cmd(s, '\'');
	else if (quote % 2 && dquote % 2)
	{
		c = ft_strrchr(s, '\'') < ft_strrchr(s, '\"') ? '\'' : '\"';
		dest = complete_cmd(s, c);
	}
	else
		dest = s;
	return (dest);
}

char		**parse(char *s)
{
	size_t			nb;
	char			**cmd;

	nb = bloc_counter(s, 0, 0);
	cmd = (char **)malloc(sizeof(char *) * (nb + 1));
	cmd[nb] = NULL;
	cmd = fill_cmd(s, cmd, 0, 0);
	ft_display_tab(cmd, "cmd");
	return (cmd);
}
