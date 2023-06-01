/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:48:35 by sizquier          #+#    #+#             */
/*   Updated: 2023/06/01 20:52:16 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset_builtin2(char *cmd, char ***env)
{
	int		i;
	int		j;
	char	**new_env;
	char	*cmd2;

	j = 0;
	if (!cmd)
		return (0);
	new_env = (char **) malloc((arr_size(*env) + 1) * sizeof(char *));
	cmd2 = ft_strjoin(cmd, "=", 0);
	i = -1;
	while ((*env)[++i]) 
		if ((ft_strncmp((*env)[i], cmd2, ft_strlen(cmd2)) != 0) && (ft_strncmp((*env)[i], cmd, ft_strlen(cmd) + 1) != 0))
			new_env[j++] = ft_strdup((*env)[i]);
	new_env[j] = NULL;
	free_dblearray((void **)*env); 
	*env = new_env;
	free(cmd2);
	return (0);
}

int	ft_unset_builtin(char	**cmd, char	***env)
{
	int	i;

	i = 1;
	while (cmd[i])
		ft_unset_builtin2(cmd[i++], env);
	return (0);
}
