/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:15:13 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/08 17:34:06 by Dugonzal         ###   ########.fr       */
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

// con esta funcion los voy metiendo en un puntero puntero mientras no sea null;|
t_cmd **last_back(t_cmd **cmd, t_cmd *new)
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
  new->prev = tmp;
  return (cmd);
}

t_cmd	*new_node(char **str, int size)
{
  t_cmd		*tmp;
  int		i;

  if (!str)
	return (NULL);
  tmp = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
  tmp->cmd = (char **)ft_calloc(size + 1, sizeof(char *));
  if (tmp->cmd == NULL || tmp == NULL)
	return (NULL);
  i = -1;
  while (++i < size)
	tmp->cmd[i] = str[i];
  tmp->type = type(str[size]);
  tmp->next = NULL;
  tmp->prev = NULL;
  tmp->cmd[size] = NULL;
  return (tmp);
}

// quiero ir metiendo los comandos primero en una arrray y
// luego a un puntero puntero
int parser_cmds(char **bufer, t_cmd **cmd)
{
  int	size;

  size = size_node(bufer);
  if (!size)
	return (0);
  last_back(cmd, new_node(bufer, size));
  return (size);
}

int execute(t_cmd *cmd, t_data *data)
{
  if (builtins(cmd, data))
	return (1);
  else
	  bin_execute (cmd, data);
  return (0);
}

void exec(t_cmd *cmd, t_data *data)
{
  t_cmd *tmp;

  tmp = cmd;
  while (tmp)
  {
	printf ("type: [%d]  ", tmp->type);
	lexer_errors(tmp->cmd);
	print (tmp->cmd);
	execute(tmp, data);
	tmp = tmp->next;
  }
}

int	parser(t_data *data)
{
  t_cmd		*cmd;
  int		i;

  i = 0;
  print (data->bufer);
  ft_bzero (&cmd, sizeof(cmd));
  while (data->bufer[i])
	if (search("|;" ,data->bufer[i][0]))
	  i++;
	else if (data->bufer[i])
	  i += parser_cmds(&data->bufer[i], &cmd);
	else if (!data->bufer[i])
		break;
  free (data->bufer);
  if (cmd)
	exec(cmd, data);
  return (0);
}
