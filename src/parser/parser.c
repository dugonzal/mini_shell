/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:15:13 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/09 11:54:06 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void free_cmd(t_cmd *cmd)
{
  t_cmd *tmp;
  
  tmp = NULL;
  while (tmp)
  {
	cmd = tmp;
	free_array(tmp->cmd);
	free (tmp);
	tmp = cmd->next;
  }
  cmd = NULL;
}

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
	//lexer_errors(tmp->cmd);
	quotes_quit(tmp->cmd, "\"\'");
	//print (tmp->cmd);
	execute(tmp, data);
	tmp = tmp->next;
  }
}

int  redir(t_cmd *cmd, char **str)
{
  int i;
  
  i = -1;
  while (str[++i])
  if (search(">", str[i][0]) && !str[i][1])
  {
	  cmd->io = 1; //out
	  cmd->file = ft_strdup(str[i + 1]);
	  str[i] = NULL;
	  str[i + 1] = NULL;
	  printf ("file: [%s]\n", cmd->file);
  }
  else if (search("<", str[i][0]) && !str[i][1])
  {
	cmd->io = 0; //in 
	cmd->file = ft_strdup(str[i + 1]);
	str[i] = NULL;
	str[i + 1] = NULL;
	printf ("file: [%s]\n", cmd->file);
  }
  return (0);
}

int parser_cmd(t_cmd *cmd, t_data *data)
{
 t_cmd *tmp;
 
  tmp = cmd;
  while (tmp)
  {
	if (redir(cmd ,tmp->cmd))
	  return (1);
	print (tmp->cmd);
	tmp = tmp->next;
  }
  //(void)data;
  exec (cmd, data);
  return (0);
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
	parser_cmd(cmd, data);
  free_cmd(cmd);
  return (0);
}


