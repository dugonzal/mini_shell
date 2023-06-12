/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 10:24:55 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/12 02:24:18 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	**last_back_node(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*tmp;

	if (!new)
		return (cmd);
	tmp = *cmd;
	if (!*cmd)
	{
		*cmd = new;
		return (cmd);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	tmp->back = tmp;
	return (cmd);
}

t_cmd	*new_node(char **str, int size)
{
	t_cmd	*tmp;
	int		i;

	if (!str)
		return (NULL);
	tmp = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!tmp)
		return (NULL);
	tmp->cmd = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!tmp->cmd)
		return (NULL);
	i = -1;
	while (++i < size)
		tmp->cmd[i] = str[i];
	tmp->cmd[size] = NULL;
	tmp->type = type(str[size]);
	tmp->next = NULL;
	tmp->back = NULL;
	return (tmp);
}

void	error_fd(void)
{
	perror(RED"dup: "RESET);
	g_status = 1;
	return ;
}
