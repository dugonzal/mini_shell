/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:05:32 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/12 13:50:08 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int  redir(t_cmd *cmd, char **str)
{
  int i;
  
  i = -1;
  while (str[++i])
  if (search(">", str[i][0]) && !str[i][1])
  {
	  cmd->io = 1; //out
	  cmd->file = ft_strdup (str[i + 1]);
	  printf ("file=[%s]\n", cmd->file);
	  str[i] = NULL;
	  str[i + 1] = NULL;
	  break ;
  }
  else if (search("<", str[i][0]) && !str[i][1])
  {
	cmd->io = 0; //in 
	cmd->file = ft_strdup (str[i + 1]);
	printf ("file=[%s]\n", cmd->file);
	str[i] = NULL;
	str[i + 1] = NULL;
  }
  return (0);
}
