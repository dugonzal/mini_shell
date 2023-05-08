/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:15:13 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/08 19:00:34 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int execute(t_cmd *cmd, t_data *data)
{
  if (builtins(cmd, data))
	return (1);
  else
	  bin_execute (cmd, data);
  return (0);
}

int parser_cmds(char **bufer, t_cmd **cmd)
{
  int	size;

  size = size_node(bufer);
  last_back_node(cmd, new_node(bufer, size));
  return (size);
}

void exec(t_cmd *cmd, t_data *data)
{
  t_cmd *tmp;

  tmp = cmd;
  while (tmp)
  {
	//printf ("type: [%d]  ", tmp->type);
	lexer_errors(tmp->cmd);
	quotes_quit(tmp->cmd, "\"\'");
	//print (tmp->cmd);
	execute(tmp, data);
	tmp = tmp->next;
  }
}

int	parser(t_data *data)
{
  t_cmd		*cmd;
  int		i;

  i = 0;
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
