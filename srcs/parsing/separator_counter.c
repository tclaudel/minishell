#include "minishell.h"

size_t		separator_counter(char *s, size_t i, size_t block)
{
	while (s[i] && s[i] != '\n')
	{
		i += ft_count_whitespaces(s + i);
		if (s[i] && s[i] == '\"')
			quotes_splitter(s, &i, '\"');
		else if (s[i] && s[i] == '\'')
			quotes_splitter(s, &i, '\'');
		else if (s[i] && !ft_strchr(" \t\'\"", s[i])
			&& !ft_strchr("|<>", s[i]))
			while (s[i] && !ft_strchr(" \t\'\"", s[i])
				&& !ft_strchr("|<>", s[i]))
				i++;
		else if (s[i] && (ft_strchr("|<>", s[i]) || ft_strcmp(">>", s + i)))
		{
			block++;
			if (!ft_strncmp(">>", s + i, 2))
				i++;
			i++;
		}
	}
	return (block);
}
