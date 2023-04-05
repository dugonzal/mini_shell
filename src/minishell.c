/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dugonzal <dugonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:01:34 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/05 10:49:13 by dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Buscar y ejecutar el ejecutable correcto (basado en
// la variable PATH o mediante el
//uso de rutas relativas o absolutas)
// Ejecutar el comando con sus argumentos
// Esperar a que el comando termine su ejecución
// Mostrar el prompt de nuevo

int	main(int ac, char **av, char **env)
{
	t_data	*mini;
	int		status;

	(void)av;
	(void)ac;
	(void)env;
	mini = (t_data *)malloc(sizeof(t_data));
	if (!mini)
		exit(EXIT_FAILURE);
	ft_memset (mini, 0, sizeof(t_data));
	status = 1;
	while (status)
	{
		mini->line = readline (BLUE"minishell$GUEST$> "RESET);
		add_history (mini->line);
		if (!ft_strncmp(mini->line, "exit", 4))
			status = 0;
		free (mini->line);
	}
	return (0);
}
