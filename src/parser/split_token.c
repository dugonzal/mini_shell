/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 09:03:08 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/27 18:17:36 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// voy a quitar las comilla y comprobar que hayan dos
//No interpretar comillas sin cerrar o caracteres especiales no especificados en el
//enunciado como \ (barra invertida) o ; (punto y coma).
// voy hacer primero el caso en el que los caracteres entre comillas no tienen
// espacios luego con espacio
static int	count_word(char *str, char *set)
{
	int count;
	char *quotes;

	quotes = "\"\'";
	count = 0;
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

char *token_split(char *str, char c)
{
  char *tmp;
  int i;
 
  i = 0;
  while (str[i] && str[i] == c)
	i++;
  tmp = ft_strndup(str, i);
  if (!tmp)
	return (NULL);
  return (tmp);
}

// contempla el caso de que haya espacios entre comillas
char **split_token(char *prompt, char *set)
{
  char **tmp;
  int word;
  int size;

  if (!prompt || !set)
	return (NULL);
  word = 0;
  tmp = (char **)malloc(sizeof(char *) * (count_word(prompt, set) + 1));
  if (!tmp)
	return (NULL);
  while (*prompt)
  {
	if (*prompt && _find("\"\'", *prompt)) // si es una comillas
	{
	  size = count_row_quotes(prompt);
	  tmp[word] = ft_strndup(prompt, size);
	  if (!tmp[word] || !(ft_strlen(tmp[word]) > 1) || tmp[word][size - 1] != tmp[word][0])
		return(ft_putstr_fd(RED"Error: quotes no closed \n"RESET, 2), free_array(tmp));
	  prompt += size;
	  word++;
	}
	else if (*prompt && !_find(set, *prompt) && !_find("\"\'", *prompt)) // si es un caracteres
	{
	  if (_find("<|>", *prompt))
	  {
		tmp[word] = token_split(prompt, *prompt);
		if (!tmp[word])
		  return(free_array(tmp));
		prompt += ft_strlen(tmp[word]);
		word++;
		continue;
	  }
	  size = _count_row(prompt, set);
	  tmp[word] = ft_strndup(prompt, size);
	  if (!tmp[word])
		return(free_array(tmp));
	  prompt += size;
	  word++;
	}
	else
		prompt++;
  }
  tmp[word] = NULL;
  return (tmp);
}
