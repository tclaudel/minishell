#include "minishell.h"

void	end_quotes(char *s, size_t *i, size_t *j, char *dest)
{
	char quote;

	while (s[*i] && s[*i] != '\'' && s[*i] != '\"')
		dest[(*j)++] = s[(*i)++];
	if ((*i) == 0 || s[(*i) - 1] != ' ' ||
		s[(*i) - 1] != '\'' || s[(*i) - 1] != '\"')
	{
		if (s[*i] == '\'')
			dest[(*j)++] = s[(*i)++];
		else
			(*i)++;
		quote = s[(*i)];
		while (s[(*i)] && s[(*i)] != quote)
			dest[(*j)++] = s[(*i)++];
		i++;
	}
	else
	{
		dest[(*j)++] = s[(*i)++];
		while (s[*i] && s[*i] != '\'' && s[*i] != '\"')
			dest[(*j)++] = s[(*i)++];
		dest[(*j)++] = s[(*i)++];
	}
}

char	*join_quotes(char *s, size_t i, size_t j)
{
	char	*dest;

	dest = (char *)ft_calloc(sizeof(char *), ft_strlen(s) + 1);
	while (s[i])
	{
		if (ft_strchr(s + i, '\'') || ft_strchr(s + i, '\"'))
			end_quotes(s, &i, &j, dest);
		else
		{
			while (s[i])
				dest[j++] = s[i++];
		}
	}
	ft_strdel(&s);
	return (dest);
}
