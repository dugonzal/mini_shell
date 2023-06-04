/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:02:47 by sizquier          #+#    #+#             */
/*   Updated: 2023/06/04 00:50:50 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	export_pwd(char *cmd, t_data *data)
{
	char	*pwd;
	char	*path;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	path = ft_strjoin(cmd, pwd, 0);
	if (!path)
		return (1);
	else if (ft_export_builtin_individual(path, data))
		return (free(pwd), free(path), 1);
	return (free(pwd), free(path), 0);
}

int	cd_argument(t_data *data)
{
	char	*home;

	home = ft_getenv_builtins("HOME", data->env);
	if (!home)
		return (1);
	if (export_pwd("OLDPWD=", data))
		return (1);
	if (chdir(home) != 0)
	{
		ft_printf(RED"cd: %s: %s\n"RESET, home, strerror(errno));
		free(home);
		perror("cd: ~");
		return (1);
	}
	if (export_pwd("PWD=", data))
		return (1);
	free(home);
	return (0);
}

int	ft_cd_builtin(t_cmd *cmd, t_data *data)
{
	char	*path;

	if (arr_size(cmd->cmd) > 2)
	{
		data->status = 1;
		return (ft_printf(RED"minishell: cd: too many arguments\n"RESET));
	}
	if (!cmd->cmd[1] || (cmd->cmd[1][0] == '~' && cmd->cmd[1][1] == '\0'))
		return (cd_argument(data));
	else if (cmd->cmd[1][0] == '-' && cmd->cmd[1][1] == '\0')
		path = ft_getenv_builtins("OLDPWD", data->env);
	else
		path = cmd->cmd[1];
	if (export_pwd("OLDPWD=", data))
		return (1);
	if (chdir(path) != 0)
	{
		ft_printf(RED"minishell: cd: %s: %s\n"RESET, path, strerror(errno));
		return (1);
	}
	if (export_pwd("PWD=", data))
		return (1);
	return (0);
}
