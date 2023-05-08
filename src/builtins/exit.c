/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:04:21 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/08 13:25:03 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//Exit status:
//  125  if the env command itself fails
//  126  if COMMAND is found but cannot be invoked
//  127  if COMMAND cannot be found
//  -    the exit status of COMMAND otherwise
void	ft_exit(t_data  *data)
{
	data->status = 0;
	ft_putstr_fd (BLUE" Goodbye :D\n"RESET, 0);
	return ;
	// habra que liberar la memoria xd; aunque se libera parte ha habra
}
