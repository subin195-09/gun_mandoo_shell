#include "minishell.h"

int	redirect_count(char *arg)
{
	int	qq_f;
	int	q_f;
	int	i;
	int	count;

	i = -1;
	qq_f = 1;
	q_f = 1;
	count = 1;
	while (arg[++i])
	{
		if (arg[i] == '\'')
			q_f *= -1;
		else if (arg[i] == '\"')
			qq_f *= -1;
		if (q_f > 0 && qq_f > 0 && (arg[i] == '>' || arg[i] == '<'))
		{
			if (arg[i + 1] == '>')
				i++;
			if (arg[i + 1])
				count++;
			count++;
		}
	}
	return (count);
}

void	sep_redirect(char ***rt, int *size, char *arg)
{
	char	temp[1024];
	int		qq_f;
	int		q_f;
	int		j;

	j = 0;
	qq_f = 1;
	q_f = 1;
	ft_memset(temp, 0, 1024);
	while (*arg)
	{
		if (*arg == '\'')
			q_f *= -1;
		else if (*arg == '\"')
			qq_f *= -1;
		if (q_f > 0 && qq_f > 0 && (*arg == '>' || *arg == '<'))
		{
			if (ft_strlen(temp) > 0)
			{
				(*rt)[*size] = ft_strdup(temp);
				ft_memset(temp, 0, 1024);
				j = 0;
				(*size)++;
			}
			temp[j++] = *arg;
			if (*(arg + 1) == '>')
				temp[j++] = *(arg++);
			(*rt)[*size] = ft_strdup(temp);
			ft_memset(temp, 0, 1024);
			j = 0;
			(*size)++;
		}
		else
			temp[j++] = *arg;
		arg++;
	}
	if (ft_strlen(temp) > 0)
	{
		(*rt)[*size] = ft_strdup(temp);
		(*size)++;
	}
}

char	**split_redirect(char **b_arg)
{
	char	**rt;
	int		size;
	int		i;

	size = 0;
	i = -1;
	while (b_arg[++i])
		size += redirect_count(b_arg[i]);
	rt = (char **)malloc(sizeof(char *) * (size + 1));
	rt[size] = 0;
	i = -1;
	size = 0;
	while (b_arg[++i])
	{
		if (redirect_count(b_arg[i]) == 1)
			rt[size++] = ft_strdup(b_arg[i]);
		else
			sep_redirect(&rt, &size, b_arg[i]);
	}
	return (rt);
}

int	find_file_name(char *arg)
{
	int	i;

	i = 1;
	while (ft_strchr(SEP, arg[i]))
		i++;
	if (arg[i] == '>' || arg[i] == '<' || !arg[i])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	redirect_check(char *arg)
{
	int	qq_f;
	int	q_f;
	int	i;

	qq_f = 1;
	q_f = 1;
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '\'')
			q_f *= -1;
		else if (arg[i] == '\"')
			qq_f *= -1;
		if (q_f > 0 && qq_f > 0 && (arg[i] == '>' || arg[i] == '<'))
		{
			if (arg[i + 1] == '>')
				i++;
			if (find_file_name(&arg[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	syntax_check(t_nd *nd)
{
	char	*tmp;
	t_nd	*tmp_nd;
	char	**before_arg;
	int		i;

	i = -1;
	if (redirect_check(nd->args[0]))
		return (EXIT_FAILURE);
	tmp_nd = nd;
	while (tmp_nd)
	{
		tmp = ft_strdup(tmp_nd->args[0]);
		free(tmp_nd->args[0]);
		free(tmp_nd->args);
		before_arg = split_qoute(tmp, SEP);
		tmp_nd->args = split_redirect(before_arg);
		free(tmp);
		if (tmp_nd->sible)
			tmp_nd = tmp_nd->sible;
		else
			break ;
	}
	i = 0;
	while (before_arg[i])
		free(before_arg[i++]);
	free(before_arg);
	return (EXIT_SUCCESS);
}
