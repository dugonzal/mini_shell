/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:19:41 by sizquier          #+#    #+#             */
/*   Updated: 2023/06/09 22:42:53 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		ft_printf(BLUE"%s\n"RESET, env[i]);
}
