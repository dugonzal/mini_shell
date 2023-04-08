/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciclo <ciclo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:58:16 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/08 21:26:33 by ciclo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 1); // handle signal ctrl + c
		write (1, "\n", 1);
		printf ("recibido ctrl + c\n");
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_redisplay();
		printf ("recibido ctrl + d");
		//exit(0); // handle signal ctrl + d

	}
	// handle signal ctrl + c and ctrl + d

}

void signals(void)
{
	struct sigaction sa;

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
