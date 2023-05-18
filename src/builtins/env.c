/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:19:41 by sizquier          #+#    #+#             */
/*   Updated: 2023/05/18 10:37:43 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(char **env, t_data *data)
{
	int	i;

	i = -1;
	while (env[++i])
	  ft_printf ("%s\n", env[i]);
	data->status = 0;
}
