#include "minishell.h"

char			*complete_cmd(char *s, char c)
{
	char		*str;
	char		buff[1024];
	int			ret;

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
	s = ft_strfjoin(s, str, 3);
	return (s);
}

size_t			bloc_counter(char *s, size_t i, size_t block)
{
	while (s[i] && s[i] != '\n')
	{
		i += ft_count_whitespaces(s + i);
		if (s[i] == '\"')
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

static char		*clear_str(char *s)
{
	size_t	i;
	char	c;
	char	*var;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			c = s[i];
			if (s[i - 1] != ' ')
			{
				var = ft_substr(s, i + 1, ft_charpos(s + i + 1, c));
				s = ft_insert(s, var, i, ft_strlen(var) + 2);
				i += ft_strlen(var);
				ft_strdel(&var);
			}
			else
				i += ft_charpos(s + i + 1, c) + 2;
		}
		else
			i++;
	}
	return (s);
}

char			**parse(char *s)
{
	size_t		nb;
	char		**cmd;

	s = clear_str(s);
	nb = bloc_counter(s, 0, 0);
	cmd = (char **)malloc(sizeof(char *) * (nb + 1));
	cmd[nb] = NULL;
	cmd = fill_cmd(s, cmd, 0);
	return (cmd);
}
