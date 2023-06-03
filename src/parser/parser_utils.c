/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:07:01 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/03 10:25:32 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	size_node(char **str)
{
	int	i;

	i = -1;
	while (str[++i] && !search("|;", str[i][0]))
		;
	return (i);
}

int	type(char *str)
{
	if (!str)
		return (3);
	else if (search(str, ';'))
		return (4);
	else if (search(str, '|'))
		return (5);
	else
		return (-1);
}

static int	count_word(char *str, char quote)
{
	int	j;
	int	count;

	count = 0;
	if (*str == quote)
		j = 1;
	else
		j = 0;
	while (str[j])
	{
		if (str[j] == quote)
			j++;
		j++;
		count++;
	}
	return (count);
}

static char	*quit_quotes(char *str, char quote)
{
	char	*tmp;
	int		i;

	tmp = (char *)ft_calloc(count_word(str, quote) + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (*str == quote)
			str++;
		tmp[i++] = *str++;
	}
	tmp[i] = 0;
	return (tmp);
}

// echo hola"hola""hola"hola -> echo holahola
void	seach_quotes(char **str, char *quotes)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (search(quotes, str[i][j]))
			{
				tmp = quit_quotes(str[i], str[i][j]);
				free(str[i]);
				str[i] = tmp;
				break ;
			}
		}
	}
}
