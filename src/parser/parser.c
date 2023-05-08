/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:15:13 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/08 10:19:26 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	size_cmd(char **str)
{
  int	i;

  i = 0;
  while (str[i] && !search("|;", str[i][0])) // intento copiar tambienl el type
	i++;
  //printf ("[%d] <--> [%s]\n", i, str[i]);
  return (i);
}

int type(char *str)
{
 // printf ("type ->[%s]\n", str);
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
  if (!tmp)
	return (cmd);
  while (tmp->next)
	  tmp = tmp->next;
  return (cmd);
  tmp->next = new;
  new->prev = tmp;
  return (cmd);
}

t_cmd	*new_cmd(char **str, int size)
{
  t_cmd		*cmd;
  int		i;

  if (!str)
	return (NULL);
  cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
  cmd->cmd = (char **)ft_calloc(size + 1, sizeof(char *));
  if (cmd->cmd == NULL || cmd == NULL)
	return (NULL);
  i = -1;
  while (++i <= size)
	cmd->cmd[i] = str[i];
  cmd->type = type(cmd->cmd[size]);
  cmd->cmd[size] = NULL;
  printf ("type ->[%d] ultimo arrray ->[%s] \n", cmd->type, cmd->cmd[size]);
  cmd->next = NULL;
  cmd->prev = NULL;
  cmd->size = size;
  return (cmd);
}

// quiero ir metiendo los comandos primero en una arrray y
// luego a un puntero puntero
int parser_cmds(char **bufer, t_cmd **cmd)
{
  t_cmd *tmp;
  int	size;

  tmp = *cmd; 
  size = 0;
  size = size_cmd(bufer);
  //printf ("%d", size);
  tmp = new_cmd(bufer, size);
  //printf ("%s]]\n",tmp->cmd[0]);
  //cmd = last_back(cmd, tmp);
  (void)tmp;
  return (size);
}



int	parser(t_data *data)
{
  t_cmd	*cmd;
  int  i;

/// necesito varias funcione para pasar los argumentos a la lista enlzadad pero no quiero xd
  /// muchas funciones hacen que sea maas largo, y literal no hay opcion
  i = -1 ;
  cmd = NULL;
  while (data->bufer[++i])
	if (data->bufer[i])
	  i += parser_cmds(&data->bufer[i], &cmd);
  else	if (!data->bufer[i])
	  break;
  return (0);
}
