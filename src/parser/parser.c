/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:15:13 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/04 15:34:51 by Dugonzal         ###   ########.fr       */
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
  //int	i;

  cmd = (t_cmd *)malloc(sizeof(t_cmd));
  size = size_argv(data->bufer);
  cmd->size = size;
  //cmd->cmd = (char **)ft_calloc(sizeof(char *), size + 1);
  //i = 0;
  //while (i < size)
  //{
//	cmd->cmd[i] = (data->bufer[i]);
//	i++;
 // 
  // }
  //cmd->cmd[i] = NULL;
 // print (cmd->cmd);
 printf ("size = %d\n", cmd->size);
  return (0);
}
