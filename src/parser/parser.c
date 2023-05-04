/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:15:13 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/04 17:42:15 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// voy a quitar las comilla y comprobar que hayan dos
//No interpretar comillas sin cerrar o caracteres especiales no especificados en el
//enunciado como \ (barra invertida) o ; (punto y coma).
// voy hacer primero el caso en el que los caracteres entre comillas no tienen
// espacios luego con espacio

int	size_argv(char **str)
{
  int	i;

  i = -1;
  while (str[++i] && !search("|;", str[i][0]))
	;
  return (i + 1);
}


int	parser(t_data *data)
{
  t_cmd	*cmd;
  int	size;
  int	i;

  cmd = (t_cmd *)malloc(sizeof(t_cmd));
  if (!cmd)
	return (-1);
  size = size_argv(data->bufer);
  cmd->size = size;
  cmd->cmd = (char **)malloc(sizeof(char *) * (size + 1));
  if (!cmd->cmd)
	return (-1);
  i = 0;
  while (i < size)
  {
	cmd->cmd[i] = (data->bufer[i]);
	i++;
  }
  cmd->next = NULL;
  cmd->prev = NULL;
  if (cmd->cmd[i - 1] == NULL)
	cmd->type = 0;
  else if (cmd->cmd[i - 1][0] == ';')
	cmd->type = 1;
	else
	cmd->type = 2;
  printf ("cmd->type = %d\n", cmd->type);
  return (0);
}
