/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:19:41 by sizquier          #+#    #+#             */
/*   Updated: 2023/05/13 09:59:15 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env_builtin(char **envp, t_data *data)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("hola");
		if (ft_strchr(envp[i], '=') != NULL)
			ft_printf("%s\n", envp[i]);
		i++;
	}
	data->status = 0;
	exit(0);
}
