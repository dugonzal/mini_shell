/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:15:13 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/04 11:47:32 by Dugonzal         ###   ########.fr       */
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
  return (i);
}


int	parser(t_data *data)
{
  t_cmd	*cmd;
  int	size;
  int	i;

  cmd = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
  size = size_argv(data->bufer);
  cmd->cmd = (char **)ft_calloc(sizeof(char *), size + 1);
  i = -1;
  while (++i < size)
	cmd->cmd[i] = (data->bufer[i]);
  cmd->cmd[i] = NULL;
  print (cmd->cmd);
  return (0);
}
