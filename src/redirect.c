/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:05:32 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/21 08:57:32 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void tmp_re(t_cmd *cmd, char **str ,int i, int fd)
{
	 cmd->io = fd;
	 cmd->file = ft_strdup (str[i + 1]);
	 str[i] = NULL;
	 str[i + 1] = NULL;
}
// realmente no se como enfocarlo para que pueda hacer redirecciones multiples
// en el mismo comando, pero si que se hacerlo para un solo comando
int redir(t_cmd *cmd)
{
  int i;

  i = -1;
  while (cmd->cmd[++i])
	if (search(cmd->cmd[i], '<'))
		tmp_re (cmd, cmd->cmd, i, 0);
  return (0);
}
