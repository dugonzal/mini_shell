/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 13:05:56 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/11 14:17:49 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtins_2(t_cmd *cmd, t_data *data)
{
	if (!ft_strncmp(cmd->cmd[0], "exit", 5))
	{
		ft_exit(cmd, data);
		return (1);
	}
	else if (!ft_strncmp(cmd->cmd[0], "cd", 3))
	{
		ft_cd_builtin(cmd, data);
		return (1);
	}
	else if (!ft_strncmp(cmd->cmd[0], "export", 7))
	{
		ft_export_general_builtin(cmd->cmd, data);
		return (1);
	}
	else if (!ft_strncmp(cmd->cmd[0], "unset", 6))
	{
		ft_unset_builtin(cmd->cmd, &data->env, data);
		return (1);
	}
	return (0);
}

int	builtins_1(t_cmd *cmd, t_data *data)
{
	if (!ft_strncmp(cmd->cmd[0], "echo", 5))
	{
		ft_echo_builtin(cmd, data);
		return (1);
	}
	else if (!ft_strncmp(cmd->cmd[0], "env\0", 4))
	{
		env(data->env);
		data->status = 0;
		return (1);
	}
	else if (!ft_strncmp(cmd->cmd[0], "pwd", 4))
	{
		ft_pwd();
		data->status = 0;
		return (1);
	}
	return (0);
}

int	builtins(t_cmd *cmd, t_data *data)
{
	if (!cmd->cmd[0])
		return (0);
	if (cmd->type == 5)
	  return (0);
	if (builtins_1(cmd, data))
		return (1);
	else if (builtins_2(cmd, data))
		return (1);
	return (0);
}

int	builtins_exec(t_cmd *cmd, t_data *data)
{
	if (!cmd->cmd[0])
		return (0);
	if (builtins_1(cmd, data))
		return (1);
	else if (builtins_2(cmd, data))
		return (1);
	return (0);
}
