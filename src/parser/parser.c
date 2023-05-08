/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:15:13 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/08 12:34:40 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	size_cmd(char **str)
{
  int	i;

  i = 0;
  while (str[i] && !search("|;", str[i][0]))
	i++;
  return (i);
}

int type(char *str)
{
  printf ("type ->[%s]<--\n", str);
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
  cmd->cmd[size] = NULL;
  i = -1;
  while (++i < size)
	cmd->cmd[i] = str[i];
  cmd->size = size;
  cmd->type = type(str[size]);
  cmd->next = NULL;
  cmd->prev = NULL;
  return (cmd);
}

// quiero ir metiendo los comandos primero en una arrray y
// luego a un puntero puntero
int parser_cmds(char **bufer, t_cmd **cmd)
{
  int	size;

  size = size_cmd(bufer);
  last_back(cmd, new_cmd(bufer, size));
  return (size);
}

void exec(t_cmd *cmd)
{
  t_cmd *tmp;

  tmp = cmd;
  print (tmp->cmd);

}

int	parser(t_data *data)
{
  t_cmd	*cmd;
  int  i;
/// necesito varias funcione para pasar los argumentos a la lista enlzadad pero no quiero xd
  /// muchas funciones hacen que sea maas largo, y literal no hay opcion
  i = 0 ;
  cmd = NULL;
  while (data->bufer[i])
	if (search("|;" ,data->bufer[i][0]))
	{
	  i++;
	  continue;
	}
	else if (!data->bufer[i])
		break;
	else if (data->bufer[i])
	  i += parser_cmds(&data->bufer[i], &cmd);
	else
	{
	  ft_putstr_fd("error en el parser no esperado\n", 2);
		break;

  }
 if (cmd)
	 exec(cmd);
else
	printf("no hay comandos\n");
  return (0);
}
