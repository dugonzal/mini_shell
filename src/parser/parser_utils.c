/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:07:01 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/18 10:57:53 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd **last_back_node(t_cmd **cmd, t_cmd *new)
{
  t_cmd	*tmp;

  if (!new)
	return (cmd);
  tmp = *cmd;
  if (!*cmd)
  {
	*cmd = new;
	return (cmd);
  }
  while (tmp->next)
	  tmp = tmp->next;
  tmp->next = new;
  return (cmd);
}

t_cmd	*new_node(char **str, int size)
{
  t_cmd		*tmp;
  int		i;

  if (!str)
	return (NULL);
  tmp = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
  if (tmp == NULL)
	return (NULL);
  tmp->cmd = (char **)ft_calloc(size + 1, sizeof(char *));
  if (tmp->cmd == NULL)
	return (NULL);
  i = -1;
  while (++i < size)
	tmp->cmd[i] = str[i];
  tmp->cmd[size] = NULL;
  tmp->type = type(str[size]);
  tmp->next = NULL;
  return (tmp);
}

int	size_node(char **str)
{
  int	i;

  i = -1;
  while (str[++i] && !search("|;", str[i][0]))
	;
  return (i);
}

int type(char *str)
{
	if (!str) // end
	  return (3);
	else if (search(str, ';')) // break
	  return (4);
	else if (search(str, '|'))// pipe
	  return (5);
	else 
	  return (-1); // no type
}

// echo "hola""hola" -> echo holahola
void seach_quotes(char **str, char *quotes)
{
  int i;
  int j;

  i = -1;
  while (str[++i])
  {
	j = -1;
	while (str[i][++j])
	  if (search(quotes, str[i][j]))
	  {
		  printf ("[%s]\n", str[i]);
	  }
  }
  }
