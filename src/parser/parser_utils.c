/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:07:01 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/26 22:16:44 by Dugonzal         ###   ########.fr       */
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
  tmp->back = tmp;
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
  tmp->back = NULL;
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

int recursive_rara(char *str,  char quote)
{
  int  j;
  int count;

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
//                   ->""<-
// el poblema es hello""hello
char *quit_quotes(char *str, char quote)
{
  char *tmp;
  int size;
  int i;
  
  size = recursive_rara(str, quote);
  tmp = (char *)ft_calloc(size + 1, sizeof(char));
  if (!tmp)
	return (NULL);
  i = 0;
  while (*str)
  {
	while (*str == quote)
	  str++;
	tmp[i++] = *str++;
  }
  str[i] = 0;
  return (tmp);
}
// echo hola"hola""hola"hola -> echo holahola
void seach_quotes(char **str, char *quotes)
{
  int i;
  int j;
  char *tmp;
  i = -1;
  while (str[++i])
  {
	j = -1;
	while (str[i][++j])
	  if (search(quotes, str[i][j]))
	  {
		tmp = quit_quotes(str[i], str[i][j]);
		free(str[i]);
		str[i] = tmp;
		break ;
	}
  }
}


