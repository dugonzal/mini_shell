/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:58:16 by ciclo             #+#    #+#             */
/*   Updated: 2023/06/05 11:30:08 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (rl_on_new_line() == -1)
			exit(-1);
		ft_printf ("\n");
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		if (rl_on_new_line() == -1)
			exit(-1);
		rl_redisplay();
	}
}

void	handler(int sig)
{
	sig_handler(sig);
}

void	signals(void)
{

	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}
