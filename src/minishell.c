/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:01:34 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/22 12:32:33 by Dugonzal         ###   ########.fr       */
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

// lexer -> parser -> builtins -> bin_execute -> waitpid

// lexer analiza la linea de comandos y la separa en tokens para el parser
 /*
  * exepciones de erro 
  * 1. linea vacia
  * 2. comillas sin cerrar
  * 3. redirecciones sin comandos
  * 4. ;
  * 5. pipes sin comandos
  * 6 \ barra invertida
  * */
/// WhiteSpaces = " \t\v\f\r\n"
/*
 * empecemos con el lexer
 * primero verificamos si la linea esta vacia o tiene comillas sin cerrar
 * luego verificamos si hay pipes
 * luego verificamos si hay redirecciones
 * luego verificamos si hay comandos
 * si hay comandos los guardamos en un array
 * si hay redirecciones los guardamos en un array
 * si hay pipes los guardamos en un array
 * si hay comillas los guardamos en un array
 * estaria guay una funcion como split pero que ademas sea un seter como trim
 * */

int	lexer(t_data *data)
{
  if (!ft_strlen(data->line) || verify_quotes(data))
		return (1);
  data->line  = ft_strtrim(data->line, " \t\v\f\r\n", 1); 
  data->bufer = ft_split(data->line, ' ');
  add_history (data->line);
  print (data->bufer);
  //bin_execute(data);
  return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	ft_bzero (&data, sizeof(t_data));
	data.status = 1;
	while (data.status)
	{
		signals();
		data.line = readline (prompt());
		if (!data.line)
		{
			perror ("Error readline: ");
			break;  
		}
		data.env = env;
		if (lexer(&data))
		{
		  free (data.line);
		  continue; // si hay error en el lexer no se ejecuta el parser
		}
		//parser(&data);
		free (data.line);
	}
  //❯ sudo lshw -short | grep motherboard
	free (data.path);
	exit(EXIT_SUCCESS);
}
