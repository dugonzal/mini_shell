/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:58:16 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/31 12:14:57 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (rl_on_new_line() == -1) // si la nueva linea está creada, no la crees
			exit(-1); //salgo de la función
		printf("\n");
	//	rl_replace_line("", 0); // creame una nueva linea vacia
		rl_redisplay();// muestramela.
	}
	if (signum == SIGQUIT)
	{
		if (rl_on_new_line() == -1)
			exit(-1);
		rl_redisplay();//muestrame la linea, no la crees porque sigquit no la necesita.
	}

}


void	sig_handler_child_input(int signum)
{
	if (signum == SIGQUIT)
	{
		// esto falla, no deberua enseñar quit,
		// su función es no hacer nada, no mostrar nada.
		printf ("Quit: 3\n");
	}
	else if (signum == SIGINT)
	{
	//	g_status = 130;
		printf("\n");
	}
}

void	handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	sig_handler(sig);
	sig_handler_child_input(sig);

}

void signals(void)
{
	struct sigaction sa;

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
