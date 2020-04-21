#include "minishell.h"

static void		standart_fill(char *s, size_t *i)
{
	(*i) += ft_strchr(s + (*i), ' ') ?
		ft_charpos(s + (*i), ' ') : ft_strlen(s + (*i));
}

static void		quotes_fill(char *s, size_t *i, char quotes)
{
	(*i)++;
	if (!s[*i])
		return ;
	(*i) += ft_charpos(s + (*i), quotes) + 1;
	if (!s[*i])
		return ;
	(*i) += ft_charpos(s + (*i), quotes);
	(*i) += ft_strchr(s + (*i), ' ') ?
		ft_charpos(s + (*i), ' ') : ft_strlen(s + (*i));
	(*i)--;
}

char			multiple_uniquotes(char *s)
{
	size_t		simple_quotes;
	size_t		double_quotes;
	char		quote;
	size_t		i;

	i = 0;
	simple_quotes = 0;
	double_quotes = 0;
	quote = 0;
	while (s[i] && s[i] != ' ')
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i];
			i += ft_charrpos(s + i + 1, quote) + 1;
			if (quote == '\'')
				simple_quotes++;
			else
				double_quotes++;
		}
		i++;
	}
	if (simple_quotes == 0 && double_quotes == 0)
		return (' ');
	i = 0;
	i += ft_charpos(s + i, quote) + 1;
	simple_quotes = 0;
	while (s[i] && s[i] != ' ')
	{
		if (s[i] == quote)
			simple_quotes++;
		i++;
	}
	return (simple_quotes % 2 ? 'd' : quote);
}

static char		set_quotes(char *s, size_t i)
{
	char quotes;

	quotes = ' ';
	if ((s + i)[0] == '\'' || (s + i)[0] == '\"')
		quotes = (s + i)[0];
	else if (ft_strchr(s + i, '\'') || ft_strchr(s + i, '\"'))
	{
		if (!ft_strchr(s + i, '\''))
			quotes = '\"';
		else if (!ft_strchr(s + i, '\"'))
			quotes = '\'';
		else
			quotes = ft_strchr(s + i, '\'') > ft_strchr(s + i, '\"') ?
				'\'' : '\"';
	}
	if (ft_charpos(s + i, quotes) > ft_charpos(s + i, ' '))
		quotes = ' ';
	return (quotes);
}

char			**fill_cmd(char *s, char **cmd, size_t i, size_t k)
{
	size_t	j;
	char	quotes;
	char	*tmp;

	while (s[i])
	{
		i += ft_count_whitespaces(s + i);
		j = i;
		if (s[i] == 0)
			break ;
		dprintf(1, "return\t: %c\n", multiple_uniquotes(s + i));
		if ((quotes = multiple_uniquotes(s + i)) != ' ' && quotes != 'd')
		{
			i += ft_charrpos(s + i, quotes) + 1;
			tmp = ft_substr(s, j, i - j - 1);
			cmd[k++] = ft_clearcharset(tmp, quotes == '\'' ? "\'" : "\"", 1);
			continue ;
		}
		if (quotes == 'd')
		{
			quotes = ft_strchr(s, '\'') ? '\'' : '\"';
			s = ft_clearcharset(s, "\'\"", 1);
		}
		quotes = set_quotes(s, i);
		if (quotes == ' ')
			standart_fill(s, &i);
		else
			quotes_fill(s, &i, quotes);
		if (ft_strchr(s + j, quotes))
			j += ft_charpos(s + j, quotes) != 0 ? 0 : 1;
		i -= (quotes != ' ' && s[i - 1] == quotes);
		cmd[k++] = ft_substr(s, j, i - j);
		i += (quotes != ' ' && s[i] == quotes);
	}
	free(s);
	return (cmd);
}
