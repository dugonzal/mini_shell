/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:15:13 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/13 12:58:49 by Dugonzal         ###   ########.fr       */
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

void copy_fd(t_data *data)
{
  data->file_in = dup(STDIN_FILENO); // copy file descriptor i\o
  data->file_in = dup(STDOUT_FILENO); // copy file descriptor i\o
}

void reset_fd(t_data *data)
{
	dup2(data->file_in, STDIN_FILENO); // copy file descriptor i\o
	dup2(data->file_out, STDOUT_FILENO); // copy file descriptor i\o
}

void exec(t_cmd *cmd, t_data *data)
{
  t_cmd *tmp;

  tmp = cmd;
  copy_fd(data);
  while (tmp)
  {
	print(cmd->cmd);
	redir(tmp, tmp->cmd);
	quotes_quit(tmp->cmd, "\"\'");
	execute(tmp, data);
	reset_fd(data);
	tmp = tmp->next;
  }
}

int parser(t_data *data)
{
  t_cmd		*cmd;
  int		i;

  i = 0;
  ft_bzero (&cmd, sizeof(cmd));
  while (data->bufer[i])
	 if (search("|;", data->bufer[i][0]))
		i++;
	else if (data->bufer[i])
		i += parser_cmds(&data->bufer[i], &cmd);
  free (data->bufer);
  if (cmd)
	exec(cmd, data);
  free_cmd(cmd);
  return (0);
}


