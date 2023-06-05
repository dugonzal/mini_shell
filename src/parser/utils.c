/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 22:05:48 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/05 09:58:26 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_open(char *str, int i)
{
	int	fd;

	fd = 0;
	if (!i)
		fd = open (str, O_RDONLY);
	else if (i == 1)
		fd = open (str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 2)
		fd = open (str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (i == 3)
		fd = open (str, O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
		ft_putendl_fd(RED"Error: No such file or directory"RESET, 2);
	return (fd);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

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

int	count_expanser(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && !search(" \t\v\f\r\"\'", str[i]))
		;
	return (i);
}
