/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 09:03:08 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/27 14:41:11 by Dugonzal         ###   ########.fr       */
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

char **split_token(char *prompt, char *set)
{
  char **tmp;
  int row;
  int word;
  char tmp_quotes;
  int size;

  if (!prompt || !set)
	return (NULL);
  row = 0;
  word = 0;
  tmp = (char **)malloc(sizeof(char *) * (count_word(prompt, set) + 1));
  if (!tmp)
	return (NULL);
  while (*prompt)
  {
	row = 0;
	if (*prompt && _find("\"\'", *prompt)) // si es una comillas
	{
	  tmp[word] = (char *)malloc(sizeof(char) * (count_row_quotes(prompt) + 1));
	  if (!tmp[word])
		return(free_array(tmp));
	  tmp_quotes = *prompt;
	  tmp[word][row++] = *prompt++;
	  while (*prompt && *prompt != tmp_quotes) 
		tmp[word][row++] = *prompt++;
	  if (*prompt != tmp_quotes)
		  return (ft_putstr_fd(RED"Error: quotation marks not closed\n"RESET, 2),free_array(tmp));
	  tmp[word][row++] = *prompt++;
	  tmp[word][row] = '\0';
	  word++;
	}
	else if (*prompt && !_find(set, *prompt) && !_find("\"\'", *prompt)) // si es un caracteres
	{
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
