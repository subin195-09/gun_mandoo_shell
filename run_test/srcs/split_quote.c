#include "minishell.h"

int		count_size(char *str, char *set)
{
	int		count;
	int		i;
	int		qq_f;
	int		q_f;
	int		flag;

	count = 1;
	i = 0;
	qq_f = 1;
	q_f = 1;
	while (str[i] && ft_strchr(set, str[i]))
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == '\"')
			qq_f *= -1;
		else if (str[i] == '\'')
			q_f *= -1;
		else if (ft_strchr(set, str[i]) && qq_f > 0 && q_f > 0)
		{
			if (ft_strchr(set, str[i + 1]))
				;
			else
				count++;
		}
		i++;
	}
	return (count);
}

char	*sep(char **str, char *set)
{
	char	*rt;
	int		i;
	int		qq_f;
	int		q_f;

	i = 0;
	qq_f = 1;
	q_f = 1;
	while (ft_strchr(set, (*str)[i]))
		(*str) += ++i;
	while ((*str)[i])
	{
		if ((*str)[i] == '\"')
			qq_f *= -1;
		else if ((*str)[i] == '\'')
			q_f *= -1;
		if (ft_strchr(set, (*str)[i]) && qq_f > 0 && q_f > 0)
		{
			if (ft_strchr(set, (*str)[i + 1]))
				;
			else
				break;
		}
		i++;
	}
	if (!(*str)[i])
	{
		if (ft_strchr(set, (*str)[i - 1]))
			i--;
		rt = ft_strndup(*str, i);
	}
	else
	{
		// if (ft_strchr(SEP, (*str)[i]))
		// 	i++;
		rt = ft_strndup(*str, i);
		(*str) += i + 1;
	}
	return (rt);
}

char	**split_quote(char *str, char *set)
{
	char	**rt;
	int		size;
	int		i;

	if (!str || !*str)
		return (NULL);
	size = count_size(str, set);
	rt = (char **)malloc(sizeof(char *) * (size + 1));
	if (!rt)
		return (NULL);
	i = -1;
	while (++i < size)
		rt[i] = sep(&str, set);
	rt[i] = 0;
	return (rt);
}
