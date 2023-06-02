/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:05:32 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/02 16:31:50 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void tmp_re(t_cmd *cmd, char **str, int i,int fd)
{
  if (str[i][0] == '<')
  {
	  printf ("l");
	 ft_strdup(str[i + 1]);
  }
  else if (str[i][0] == '>')
  {
	 printf ("a");
	 ft_strdup(str[i + 1]);
  }
  cmd->io = fd;
  str[i] = NULL;
  str[i + 1] = NULL;
}
// realmente no se como enfocarlo para que pueda hacer redirecciones multiples
// en el mismo comando, pero si que se hacerlo para un solo comando
// no interpetar recciones detro de comillas


/*
int redir(t_cmd *cmd)
{
  int i;

  i = -1;
  while (cmd->cmd[++i])
  {
	if (search(cmd->cmd[i], '<') && !search(cmd->cmd[i], '\'') \
	  && !search(cmd->cmd[i], '\"'))
	  tmp_re (cmd, cmd->cmd, i, 0);
	else if (search(cmd->cmd[i], '>') && !search(cmd->cmd[i], '\'') \
	  && !search(cmd->cmd[i], '\"'))
	  tmp_re (cmd, cmd->cmd, i, 1);
	else if (search(cmd->cmd[i], '>') && cmd->cmd[i][1] == '>' && !search(cmd->cmd[i], '\'') \
	  && !search(cmd->cmd[i], '\"'))
	{
	  cmd->fd[1] = ft_open(cmd->cmd[i + 1], 2);
	  ft_dup2 (cmd->fd, 1);
	  cmd->cmd[i] = NULL;
	  cmd->cmd[i + 1] = NULL;
	  }	
  }
  return (0);
}

*/

int redir_in(t_cmd *cmd, char **str)
{
	if (search(str[0], '<') && !str[1])
		cmd->fd[0] = ft_open(str[1], 0);
	else if (search(str[0], '<') && str[0][1] == '<')
		printf ("heredoc<");
	str[0] = NULL;
	str[1] = NULL;
	ft_dup2(cmd->fd, 0);
	return (0);
}

int redir_out(t_cmd *cmd, char **str)
{
	if (search(str[0], '>') && !str[0][1])
		cmd->fd[1] = ft_open(str[1], 1);
	else if (search(str[0], '>') && str[0][1] == '>')
		cmd->fd[1] = ft_open(str[1], 2);
	str[0] = NULL;
	str[1] = NULL;
	ft_dup2(cmd->fd, 1);
	return (0);
}
	// tendria que dividirlo en dos segementos de redireccion
	// las de entrada < << || o salida > >>
	// stdinfile, stdoutfile, stderrfile
	// si no hay redirecciones, no hace nada
	// 1 = stdout 2 = stderr 0 = stdin
int redir(t_cmd *cmd)
{
	int i;

	i = -1;
	while (cmd->cmd[++i])
		if (search(cmd->cmd[i], '<'))
			redir_in(cmd, &cmd->cmd[i]);
	i = -1;
	while (cmd->cmd[++i])
		if (search(cmd->cmd[i], '>'))
			redir_out(cmd, &cmd->cmd[i]);
	return (0);	
}










