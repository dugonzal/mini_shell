/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:07:01 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/10 14:06:29 by Dugonzal         ###   ########.fr       */
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
	char	*tmp;
	int		count;

	count = 0;
	tmp = str;
	while (*tmp++)
	{
		if (*tmp == quote)
			while (*tmp == quote)
				tmp++;
		if (*tmp != quote && *tmp != 0)
			count++;
	}
	return (count);
}

char	*quit_quotes(char *str, char quote)
{
	char	*tmp;
	int		i;	
	int		j;

	tmp  = (char *)ft_calloc(count_word(str, quote) + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
	  if (str[i] == quote)
			  i++;
	  else 
		  tmp[j++] = str[i++];
	}
	tmp[j] = 0;
	return (tmp);
}

// echo hola"hola""hola"hola -> echo holahola
void	search_quotes(t_cmd *cmd, char *quotes)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (cmd->cmd[++i])
	{
		j = -1;
		while (cmd->cmd[i][++j])
		{
			if (search(quotes, cmd->cmd[i][j]))
			{
				tmp = quit_quotes(cmd->cmd[i], cmd->cmd[i][j]);
				free(cmd->cmd[i]);
				cmd->cmd[i] = tmp;
				break ;
			}
		}
	}
}
