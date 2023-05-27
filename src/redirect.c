/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:05:32 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/26 23:59:58 by Dugonzal         ###   ########.fr       */
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
int redir(t_cmd *cmd)
{
  int i;

  i = -1;
  while (cmd->cmd[++i])
  {
	if (search(cmd->cmd[i], '<'))
	  tmp_re (cmd, cmd->cmd, i, 0);
	else if (search(cmd->cmd[i], '>') && cmd->cmd[i][1] == '>')
	{
	  cmd->fd[1] = ft_open(cmd->cmd[i + 1], 2);
	  ft_dup2 (cmd->fd, 1);
	  cmd->cmd[i] = NULL;
	  cmd->cmd[i + 1] = NULL;
	  }	
	else if (search(cmd->cmd[i], '>'))
	  tmp_re (cmd, cmd->cmd, i, 1);


  }
  return (0);
}
