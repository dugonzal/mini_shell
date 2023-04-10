/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciclo <ciclo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:26:30 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/10 21:38:30 by ciclo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*prompt(void)
{
	char	*prompt;
	char	*usuario;
	char	*anfitrion;

	if (!(usuario = getenv("USER")))
		usuario = ft_strdup("\033[1;31mAnonimo\033[0m");
	usuario = ft_strjoin("\033[1;31m", usuario, 0);
	anfitrion = ft_strjoin("\033[1;34m@minishell> \033[0m", " ", 0);
	prompt = ft_strjoin(usuario, anfitrion, 0);
	free(usuario);
	free (anfitrion);
	return (prompt);
}




