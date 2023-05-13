/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:05:32 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/13 15:55:30 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void tmp_re(t_cmd *cmd, char **str ,int i, int j)
{
	 cmd->io = j;
	 cmd->file = ft_strdup (str[i + 1]);
	 str[i] = NULL;
	 str[i + 1] = NULL;
}

int  redir(t_cmd *cmd, char **str)
{
  int i;

  i = -1;
  while (str[++i])
  if (search(">", str[i][0]) && !str[i][1])
	tmp_re (cmd, str, i, 1);
  else if (search("<", str[i][0]) && !str[i][1])
	tmp_re (cmd, str, i, 0);
  else if (search(">", str[i][0]) && search(">", str[i][1]))
  {
	cmd->fd[1] = ft_open(str[i + 1], 2);
	if (cmd->fd[1] < 0 || dup2(cmd->fd[1], 1) == -1)
	{
	  perror("dup2");
	  close(cmd->fd[1]);
	}
	str[i] = NULL;
	str[i + 1] = NULL;
	close (cmd->fd[1]);
  }
  else if (search("<", str[i][0]) && search("<", str[i][1]))
  {
	  printf ("heredoc\n");
	  str[i + 1] = NULL;
	  str[i] = NULL;
  }
  if (cmd->file && search("\"\'", cmd->file[0]))
	cmd->file = ft_strtrim(cmd->file, "\"\'", 1);
  return (0);
}
