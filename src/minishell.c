/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:01:34 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/02 16:33:11 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
Estado de salida:
 0  si todo fue bien
 1  si hubo problemas menores (p. ej., no poder acceder a un subdirectorio),
 2  si hubo un serio problema (p. ej., no se puede acceder al argumento de
 línea de órdenes)
*/

// lexer -> parser-> expanser ->  builtins -> bin_execute -> waitpid

// whitespaces = " \t\v\f\r\n"
// quotes = "\"\'"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac > 1)
	  err ("to many arguments");
	(void)av;
	ft_bzero (&data, sizeof(t_data));
	data.status = 1;
	//data.path = ft_split(getenv("PATH"), ':');
	while (data.status)
	{
		signals();
		data.line = readline (prompt());
		if (!data.line)
		 break;
		data.env = env;
		if (lexer(&data))
			continue;
		//parser(&data);
		bin_execute(&data);
		free_array (data.bufer);
	}
	free (data.path);
	exit(EXIT_SUCCESS);
}
