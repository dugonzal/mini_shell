/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciclo <ciclo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:01:34 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/10 12:18:24 by ciclo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Buscar y ejecutar el ejecutable correcto basado en
 la variable PATH o mediante el
uso de rutas relativas o absolutas)
 Ejecutar el comando con sus argumentos
 Esperar a que el comando termine su ejecución
 Mostrar el prompt de nuevo
 voy a empezar por buscar el ejecutable en el PATH*/




/*
Estado de salida:
 0  si todo fue bien
 1  si hubo problemas menores (p. ej., no poder acceder a un subdirectorio),
 2  si hubo un serio problema (p. ej., no se puede acceder al argumento de
 línea de órdenes)
*/

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)av;
	(void)ac;
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	ft_memset (data, 0, sizeof(t_data));
	data->status = 1;
	data->path = ft_split(getenv("PATH"), ':');
	while (data->status)
	{
		signals();
		data->line = readline (BLUE"minishell$GUEST$> "RESET);
		add_history (data->line);
		if (!ft_strncmp(data->line, "exit", 4))
			data->status = 0;
		data->env = env;
		parser(data);
	}
	free (data->path);
	free (data);
	exit(EXIT_SUCCESS);
}
