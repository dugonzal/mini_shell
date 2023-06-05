/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:04:21 by ciclo             #+#    #+#             */
/*   Updated: 2023/06/05 10:04:45 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_numeric_error(t_cmd	*cmd, t_data *data)
{
	data->status = 255;
	printf(RED"exit: %s: numeric argument required\n"RESET, \
		cmd->cmd[1]);
	return (0);
}

void free_program(t_cmd *cmd, t_data *data)
{
	free (data->user);
	free_cmd(cmd);
	free(data->path);
	free (data->env);
	
}

int	ft_exit(t_cmd *cmd, t_data *data)
{
	int	i;

	if (cmd->cmd[1] && cmd->cmd[2])
	{
		data->status = 1;
		ft_printf(RED"exit: too many arguments\n"RESET);
		return (1);
	}
	i = -1;
	if (cmd->cmd[1])
	{
		while (cmd->cmd[1][++i])
			if (ft_isalpha(cmd->cmd[1][i]))
				return (ft_numeric_error(cmd, data));
		data->status = ft_atoi(cmd->cmd[1]);
	}
	else
		data->status = 0;
	free_program(cmd, data);
	exit (0);
	return (0);
}
