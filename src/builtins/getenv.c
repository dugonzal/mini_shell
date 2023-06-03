/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:55:54 by sizquier          #+#    #+#             */
/*   Updated: 2023/06/03 10:01:35 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_getenv_builtins(char	*cmd, char	**env)
{
	int		i;
	int		j;
	char	*cmd2;
	char	*str;
	int		len;

	i = -1;
	j = 0;
	cmd2 = ft_strjoin(cmd, "=", 0);
	len = ft_strlen(cmd2);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], cmd2, len))
		{
			while (env[i][j] != '=' && env[i][j])
				j++;
			str = ft_substr(env[i], j + 1, ft_strlen(env[i]) - len);
			free(cmd2);
			return (str);
		}
	}
	free(cmd2);
	return (NULL);
}
