/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:03:50 by sizquier          #+#    #+#             */
/*   Updated: 2023/06/01 20:46:10 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_export_namecmd(char	*cmd)
{
	int		i;

	i = -1;
	while (cmd[++i])
		if (cmd[i] == '=')
			return (ft_strndup(cmd, i + 1));
	return (cmd);
}

int	ft_check_replace(char	*cmd, t_data *data)
{
	int		i;
	char	*name_cmd;

	if (cmd == NULL) //caso que cmd no tenga valor
		name_cmd = ft_strdup(cmd);
	else
		name_cmd = ft_export_namecmd(cmd); //lo he modificado, no se muy bien xq no coge
	i = -1;
	while (data->env[++i]) // caso que cmd tenga valor
		if (!ft_strncmp(data->env[i], name_cmd, ft_strlen(name_cmd)))
		{
			free((data->env)[i]);
			data->env[i] = ft_strdup(cmd);
			free(name_cmd);
			return (1);
		}
	if (name_cmd)
		free(name_cmd);
	return (0);
}
int	ft_generate_export(char	*cmd, t_data *data)
{
	int		i;
	char	**new_env;

	if (ft_isdigit(cmd[0]) || !ft_cmd_isalnum(cmd))
		ft_invalid(cmd);
	if (ft_check_replace(cmd, data))
		return (0);
	new_env = (char **) malloc((arr_size(data->env) + 2) * sizeof(char *));
	i = -1;
	while (data->env[++i])
		new_env[i] = ft_strdup(data->env[i]);
	new_env[i++] = ft_strdup(cmd);
	new_env[i] = NULL;
	free_dblearray((void **)data->env);
	data->env = new_env;
	return (0);
}


int	ft_export_builtin_individual(char *cmd, t_data *data)
{
	int	found;

	if (cmd[0] == '=')
	{
		data->status = 1;
		ft_printf("export: '%s': not a valid identifier\n", cmd);
		return (1);
	}
	if (ft_strlen(cmd) > 0 && !search(cmd, '='))
		return (ft_generate_export(ft_strjoin(cmd, "=\'\'", 1), data));
	found = ft_check_replace(cmd, data);
	if (found == 0)
	{
		printf("Enterning generate export with arg %s\n", cmd);
		ft_generate_export(cmd, data);
	}
	return (0);
}

int	ft_export_general_builtin(char	**cmd, t_data *data)
{
	int	i;

	data->status = 0;
	if (!cmd[1])
	{
		i = 0;
		while (data->env[i])
			printf("declare -x %s\n", data->env[i++]);
		return (1);
	}
	i = 0;
	while (cmd[++i])
		ft_export_builtin_individual(cmd[i], data);
	return (1);
}
