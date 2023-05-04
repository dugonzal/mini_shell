/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:04:21 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/04 15:18:48 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(t_data  *data)
{
	data->status = 0;
	printf (BLUE" Goodbye :D\n");
	return ;
	// habra que liberar la memoria xd;
}
