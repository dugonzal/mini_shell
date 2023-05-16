/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:15:13 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/16 10:34:17 by Dugonzal         ###   ########.fr       */
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

  fd = dup(0);
  if (fd == -1)
	error_fd(data);
  data->fd_in = fd;
  fd = dup(1);
  if (fd == -1)
	error_fd(data);
  data->fd_out = fd;
}

void reset_fd(t_data *data)
{
	if (dup2(data->fd_in, 0) == -1)
	{
	  perror("dup2");
	  data->status = 1;
	  close(data->fd_in);
	  close(data->fd_out);
	  return ;
	}
	close (data->fd_in);
  	if (dup2(data->fd_out, 1) == -1)
	{
	  perror("dup2");
	  data->status = 1;
	  close(data->fd_out);
	  return ;
	}
	close (data->fd_out);
}

int search_array(char **str)
{
  int i;

  i = -1;
  while (str[++i])
  {
	if (search(str[i], '<') || search(str[i], '>'))
	{
	  printf ("----- %s\n", str[i]);
	  return (1);
	}
  }
  return (0);
}

void exec(t_cmd *cmd, t_data *data)
{
  t_cmd *tmp;

  tmp = cmd;
  copy_fd(data);
  while (tmp)
  {
	redir(tmp, tmp->cmd); // searria una solucion rapida // ? podran haber mas de 2 redirecciones
	seach_quotes(tmp->cmd, "\"\'");
	execute(tmp, data);
	if (tmp->type != 5)
	  reset_fd(data);
	
/*
 *
 * nese que pasa con esto xd
 * */
	redir(tmp, tmp->cmd); // redir xd
	
/**
 * eso etenmos que redireccionar de entrada y salida
 **/

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


