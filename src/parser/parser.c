/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:15:13 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/13 16:16:43 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int execute(t_cmd *cmd, t_data *data)
{
  if (cmd->file)
	exec_redir(cmd);
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

void error_fd(t_data *data)
{
	perror("dup");
	data->status = 1; // error
	return ;
}

void copy_fd(t_data *data)
{
  int fd;

  fd = dup(STDIN_FILENO);
  if (fd == -1)
	error_fd(data);
  data->file_in = fd;
  fd = dup(STDOUT_FILENO);
  if (fd == -1)
	error_fd(data);
  data->file_out = fd;
}

void reset_fd(t_data *data)
{
	if (dup2(data->file_in, STDIN_FILENO) == -1)
	{
	  perror("dup2");
	  data->status = 1;
	  close(data->file_in);
	  close(data->file_out);
	  return ;
	}
	close (data->file_in);
  	if (dup2(data->file_out, STDOUT_FILENO) == -1)
	{
	  perror("dup2");
	  data->status = 1;
	  close(data->file_out);
	  return ;
	}
	close (data->file_out);
}

void exec(t_cmd *cmd, t_data *data)
{
  t_cmd *tmp;

  copy_fd(data);
  tmp = cmd;
  while (tmp)
  {
	//print(cmd->cmd);
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


