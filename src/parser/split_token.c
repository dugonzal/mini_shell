/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 09:03:08 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/30 15:23:14 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// voy a quitar las comilla y comprobar que hayan dos
//No interpretar comillas sin cerrar o caracteres
//especiales no especificados en el
//enunciado como \ (barra invertida) o ; (punto y coma).
// voy hacer primero el caso en el que los caracteres
// entre comillas no tienen
// espacios luego con espacio
char **split_token(char *prompt, char *set, char *specials, char *quotes)
{
  char **tmp;
  int word;
  int size;

  word = 0;
  tmp = (char **)malloc(sizeof(char *)\
  * count_word(prompt, set, quotes, specials) + 1);
  fun_check(*tmp);
  while (*prompt)
  {
	size = 0;
	if (*prompt && search(specials, *prompt)) // specials_token
	{ // reducir lineas metiendo direcatmente la funcion del size de la lina a strndup, pero tendria que avanzar hasta ese punnto
		size = specials_token(prompt);
		tmp[word++] = fun_check(ft_strndup(prompt, size));
	}
	else if (*prompt && !search(specials, *prompt) // caracteres_token
	&& !search(quotes, *prompt) && !search(set, *prompt))
	{
	  size = caracteres_token(prompt, set, quotes, specials);
	  tmp[word++] = fun_check(ft_strndup(prompt, size));
	}
	else if (*prompt && search(quotes, *prompt))
	{
	  size = quotes_token(prompt, *prompt);
	  tmp[word++] = fun_check(ft_strndup(prompt, size));
	}
	else
		prompt++;
	prompt += size;
  }
  tmp[word] = NULL;
  return (tmp);
}
