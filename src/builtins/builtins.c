/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 13:05:56 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/26 21:47:59 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int builtins(t_cmd *cmd, t_data *data)
{
  if (!ft_strncmp(cmd->cmd[0], "exit", ft_strlen(cmd->cmd[0])))
  {
    //ft_exit(cmd, data);
    return (1);
  }
  else if (!ft_strncmp(cmd->cmd[0], "pwd", ft_strlen(cmd->cmd[0])))
  {
    ft_pwd();
    return (1);
  }
  else if (!ft_strncmp(cmd->cmd[0], "echo", ft_strlen(cmd->cmd[0])))
  {
    ft_echo_builtin(cmd);
    return (1);
  }
   else if (!ft_strncmp(cmd->cmd[0], "env", ft_strlen(cmd->cmd[0])))
  {
    ft_env(data->env);
    return (1);
  }
   else if (!ft_strncmp(cmd->cmd[0], "export", ft_strlen(cmd->cmd[0])))
  {
//	ft_export_general_builtin(cmd->cmd, &data->env);
    return (1);
  }
  return (0);
}

