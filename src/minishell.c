/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciclo <ciclo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:01:34 by ciclo             #+#    #+#             */
/*   Updated: 2023/03/17 12:34:59 by ciclo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Buscar y ejecutar el ejecutable correcto (basado en la variable PATH o mediante el
//uso de rutas relativas o absolutas)
// Ejecutar el comando con sus argumentos
// Esperar a que el comando termine su ejecución
// Mostrar el prompt de nuevo


int	main(int ac, char **av, char **env)
{
	t_data *mini;
	int status;
	(void)av;
	(void)ac;
	char *line;
	(void)env;
	mini = (t_data *)malloc(sizeof(t_data));
	if (!mini)
		return (-1);
	ft_memset (mini, 0, sizeof(t_data));
	status = 1;
	while (status)
	{
		line = readline (BLUE"minishell$GUEST$> "RESET);
  	 	add_history (line); // add to history
 		if (ft_strncmp(line, "exit", 4) == 0)
			status = 0;
		free (mini->line);
	}
	return (0);
}
