#include "minishell.h"

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

char			multiple_quotes(char *s, size_t squote, size_t dquote)
{
	size_t		i;

	i = 0;
	if (!ft_strchr(s, '\'') && !ft_strchr(s, '\"'))
		return (' ');
	while (s[i] && s[i] != ' ')
	{
		if (s[i] == '\'')
			squote++;
		else if (s[i] == '\"')
			dquote++;
		i++;
	}
	if (squote % 2 || dquote % 2)
	{
		if (!ft_strchr(s, '\''))
			return ('\"');
		else if (!ft_strchr(s, '\"'))
			return ('\'');
		else
			return (ft_charpos(s, '\'') < ft_charpos(s, '\"') ? '\'' : '\"');
	}
	return ('s');
}

static char		utils(char **s, char quotes, size_t *i, size_t *j)
{
	if (quotes == 's')
	{
		quotes = ft_strchr((*s), '\'') ? '\'' : '\"';
		(*s) = ft_clearcharset((*s), "\'\"", 1);
	}
	quotes = set_quotes((*s), (*i));
	if (quotes == ' ')
	{
		(*i) += ft_strchr(*s + (*i), ' ') ?
		ft_charpos(*s + (*i), ' ') : ft_strlen(*s + (*i));
	}
	else
		quotes_fill((*s), i, quotes);
	if (ft_strchr((*s) + (*j), quotes))
		j += ft_charpos((*s) + (*j), quotes) != 0 ? 0 : 1;
	(*i) -= (quotes != ' ' && (*s)[(*i) - 1] == quotes);
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
		if ((quotes = multiple_quotes(s + i, 0, 0)) != ' ' && quotes != 's')
		{
			i += ft_charrpos(s + i, quotes) + 1;
			tmp = ft_substr(s, j, i - j - 1);
			cmd[k++] = ft_clearcharset(tmp, quotes == '\'' ? "\'" : "\"", 1);
			continue ;
		}
		quotes = utils(&s, quotes, &i, &j);
		cmd[k++] = ft_substr(s, j, i - j);
		i += (quotes != ' ' && s[i] == quotes);
	}
	free(s);
	return (cmd);
}
