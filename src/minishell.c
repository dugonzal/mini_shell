/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dugonzal <dugonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:01:34 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/25 03:35:35 by dugonzal         ###   ########.fr       */
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
/// set la string a tokenizar y el set son los caracteres que se van a delimitar para tokenizar la string
// echo "hola mundo" | grep "hola" > file.txt
// cualquier cadena que este entre comillas dobles o simples sera un token
// primero verificamos si hay comillas dobles y luego simples


// whitespaces = " \t\v\f\r\n"
// quotes = "\"\'"

// chatgpt me decia que usara un glag para saber si estaba dentro de unas commillas o no
// si tengo set en medio de las las palabras y quotes el pricinpio de las palabras
void	*print_str(char *str, int i)
{
	printf("[%c]", str[i]);
	printf("[%d]", i);
	printf("\n");
	return (NULL);
}

int	_find(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
int _count_words(t_data *data, char *whitespace, char *quotes)
{
	char *tmp;
	int count;
	int flag;
	int i;

	count = 0;
	tmp = data->line;
	flag = 0;
	i = 0;
	(void)quotes;
	while (tmp[i])
	{
		printf ("[%c]", tmp[i]);
		if (find(quotes, tmp[i]) == 1)
			flag = 1;
		if (flag)
		{
			i++;
			while (tmp[i] && !_find(quotes, tmp[i]))
				i++;
				count++;
			flag = 0;
		}
		if (tmp[i] && !_find(whitespace, tmp[i]) && !_find(quotes, tmp[i]) && !flag)
		{
			i++;
			if (_find (quotes, tmp[i]))
				flag = 1;
			count++;
			while (tmp[i] && !_find(whitespace, tmp[i]) && !_find(quotes, tmp[i]) && !flag)
			{
				if (_find(whitespace, tmp[i]))
					break;
				else if (_find(quotes, tmp[i]))
					flag = 1;
				i++;
			}
		}
		else if (tmp[i] && _find(whitespace, tmp[i]) && !_find(quotes, tmp[i]) && !flag)
		{
			i++;
			while (tmp[i] && _find(whitespace, tmp[i]) && !_find(quotes, tmp[i]))
			{
				if (!_find(whitespace, tmp[i]))
					break;
				i++;
			}
		}
		else
			i++;
	}
	return (count);
}
int	lexer(t_data *data)
{
	char *whitespaces;
	char *quotes;

	quotes = "\"\'";
	whitespaces = " \t\v\f\r";
	if (!ft_strlen(data->line))// || verify_quotes(data))
		return (1);
	data->line = ft_strtrim(data->line, whitespaces, 1);
	int i = _count_words(data, whitespaces, quotes);
	printf("\ni = %d\n", i);
  add_history (data->line);
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
		lexer(&data);
		//parser(&data);
		free (data.line);
    free (data.bufer);
	}
  //❯ sudo lshw -short | grep motherboard
	free (data.path);
	exit(EXIT_SUCCESS);
}
