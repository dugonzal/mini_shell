/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:01:34 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/26 15:17:41 by Dugonzal         ###   ########.fr       */
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

char	*tmp_sky(char *str, char s)
{
  str++;
  while (*str && *str != s)
	str++;
  str++;
  return (str);
}
char	*tmp_sky_set(char *str, char *set, char *quotes)
{
  str++;
  while (*str && !_find(set, *str) && !_find(quotes, *str))
	str++;
  if (*str && !_find(quotes, *str))
	str++;
  return (str);
}


char	*sky(char *str)
{
  if (*str == '\'')
	str = tmp_sky(str, '\'');
  else if (*str == '\"')
	  str = tmp_sky(str, '\"');
  return (str);
}

int	_count(char *str, char *set)
{
	int count;
	char *quotes;

	quotes = "\"\'";
	count = 0;
	(void)set;
	while (*str)
	{
	  if (*str && _find(quotes, *str))
	  {
		str = sky(str);
		count++;
	  }
	  else if (*str && !_find(set, *str) && !_find(quotes, *str))
	  {
		str = tmp_sky_set(str, set, quotes);
		count++;
	  }
	  else
		str++;
	}
	return (count);
}


int count_set(char *str, char *set)
{
  int i;

  i = 0;
  while (str[i] && !_find(set, str[i]))
	i++;
  return (i);
}

char **split_token(char *prompt, char *set)
{
  char **tmp;
  int row;
  int word;
  char *quotes;
  char tmp_quotes;

  if (!prompt || !set)
	return (NULL);
  quotes = "\"\'";
  row = 0;
  word = 0;
  tmp = (char **)malloc(sizeof(char *) * (_count(prompt, set) + 1));
  if (!tmp)
	return (NULL);
  while (*prompt)
  {
	row = 0;
	if (*prompt && _find(quotes, *prompt)) // si es una comillas
	{
	  tmp[word] = (char *)malloc(sizeof(char) * (count_set(prompt, quotes) + 1));
	  if (!tmp[word])
		return(free_array(tmp));
	  tmp_quotes = *prompt;
	  tmp[word][row++] = *prompt++;
	  while (*prompt && *prompt != tmp_quotes) 
		tmp[word][row++] = *prompt++;
	  tmp[word][row++] = *prompt++;
	  tmp[word][row] = '\0';
	  word++;
	}
	else if (*prompt && !_find(set, *prompt) && !_find(quotes, *prompt)) // si es un caracteres
	{
	  tmp[word] = (char *)malloc(sizeof(char) * (count_set(prompt, set) + 1));
	  if (!tmp[word])
		return(free_array(tmp));
	  while (*prompt && !_find(set, *prompt) && !_find(quotes, *prompt))
		tmp[word][row++] = *prompt++;
	  tmp[word][row] = '\0';
	  word++;
	}
	else
	  prompt++;
	
  }
  tmp[word] = NULL;
  return (tmp);
}



int	lexer(t_data *data)
{
	char *whitespaces;

	whitespaces = " \t\v\f\r";
	if (!ft_strlen(data->line)) // || verify_quotes(data))
		return (1);
	data->line = ft_strtrim(data->line, whitespaces, 1);
	data->bufer = split_token(data->line, whitespaces);
	print(data->bufer);
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
	}
  //❯ sudo lshw -short | grep motherboard
	free (data.path);
	exit(EXIT_SUCCESS);
}
