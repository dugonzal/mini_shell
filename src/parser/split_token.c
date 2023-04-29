/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 09:03:08 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/29 11:31:29 by Dugonzal         ###   ########.fr       */
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
	char	*tmp;
	int		i;

	if (!str)
		return (NULL);
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
  (void)size;
  tmp = (char **)malloc(sizeof(char *) * (count_word(prompt, set) + 1));
  if (!tmp)
	return (NULL);
  while (*prompt)
  {
	if (*prompt && !_find("\"\'", *prompt) \
	&& !_find(set, *prompt) && !_find("<|>", *prompt)) //aqui por ejemplo solo meteria caracteres a los arrays 
	{
	  printf ("prompt = [%c]\n", *prompt);
	  prompt++;
	}
	else
		prompt++;
  }
  tmp[word] = NULL;
  return (tmp);
}
