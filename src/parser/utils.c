/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dugonzal <dugonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 22:05:48 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/18 20:55:37 by dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_open(char *str, int i)
{
	int fd;

	fd = 0;
	if (i == 0)
	  fd = open (str, O_RDONLY); //lectura
	else if (i == 1)
	  fd = open (str, O_WRONLY | O_CREAT | O_TRUNC, 0644);  //escritura
	else if (i == 2)
	  fd = open (str, O_WRONLY | O_CREAT | O_APPEND, 0644); //escritura / lectura > al final
	else if (i == 3)
	  fd = open (str, O_RDONLY | O_CREAT, 0644); //lectura / escritura
	if (fd == -1)
	  ft_putstr_fd(RED"Error: No such file or directory\n"RESET, 2);
	return (fd);
}

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
