/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:15:13 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/04 19:47:03 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

  cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
  size = size_argv(data->bufer);
  cmd->size = size;
  cmd->cmd = (char **)ft_calloc(size + 1, sizeof(char *));
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
