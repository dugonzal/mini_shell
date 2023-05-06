/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:15:13 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/06 19:56:37 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	size_argv(char **str)
{
  int	i;

  i = 0;
  while (str[i] && !search("|;", str[i - 1][0])) // intento copiar tambienl el type
	i++;
  printf ("[%d] <--> [%s]\n", i, str[i]);
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
  i = 0;
  while (i < size)
  {
	cmd->cmd[i] = str[i];
	i++;
  }
  cmd->cmd[size] = NULL;
  cmd->next = NULL;
  cmd->prev = NULL;
 // cmd->type = type(str[i]);
 // printf ("cmd->type = %d\n", cmd->type);
  //cmd->size = size;
  //printf (" = %d\n", cmd->size);
  return (cmd);
}

// quiero ir metiendo los comandos primero en una arrray y
// luego a un puntero puntero
int lista_lists(t_data *data, t_cmd **cmd)
{
  (void)data;
  (void)cmd;
  return (1);
}



int	parser(t_data *data)
{
  t_cmd	*cmd;
/// necesito varias funcione para pasar los argumentos a la lista enlzadad pero no quiero xd
  /// muchas funciones hacen que sea maas largo, y literal no hay opcion
  lista_lists(data, &cmd);
	return(1);
  return (0);
}
