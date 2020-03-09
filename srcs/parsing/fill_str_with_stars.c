#include "minishell.h"

char	*fill_str_with_var(char *s, size_t i, size_t j, char is_quote)
{
	char	*var;
	char	*value;

	is_quote = 0;
	while (s[i])
	{
		// while (s[i + 1] && s[i + 1] != '\'')
		// 	i++;
		if (s[i] == '$')
		{
			i++;
			j = i;
			while (s[j] && s[j] != '\"' && s[j] != ' ' && s[j] != '$')
				j++;
			var = ft_substr(s, i, j - i);
			if (var && var[0] == '?')
				value = ft_itoa(sh()->question_mark);
			else
				value = sh()->env->search(sh()->env, var);
			if (value)
				s = ft_insert(s, value, i - 1, ft_strlen(var) + 1);
			else 
				s = ft_insert(s, " ", i - 1, ft_strlen(var) + 1);
			i += value ? ft_strlen(value) - 1 : 0;
			ft_strdel(&var);
		}
		else
			i++;
	}
	return (s);
}
