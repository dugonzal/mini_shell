/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:05:32 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/31 12:53:31 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void tmp_re(t_cmd *cmd, char **str, int i,int fd)
{
  if (str[i][0] == '<')
  {
	  printf ("l");
	 cmd->in = ft_strdup(str[i + 1]);
  }
  else if (str[i][0] == '>')
  {
	 printf ("a");
	cmd->out = ft_strdup(str[i + 1]);
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

int redir_in(char *cmd)
{
	printf ("redir_in [%s] \n", cmd);
	return (0);
}


int redir_out(char *cmd, char *outfile)
{
	printf ("redir_out [%s] [%s]  \n", cmd, outfile);
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
			redir_in(cmd->cmd[i]);
		else if (search(cmd->cmd[i], '>'))
			redir_out(cmd->cmd[i], cmd->cmd[i + 1]);
	return (0);	
}










