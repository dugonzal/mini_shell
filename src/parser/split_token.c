/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 09:03:08 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/29 17:06:12 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// voy a quitar las comilla y comprobar que hayan dos
//No interpretar comillas sin cerrar o caracteres especiales no especificados en el
//enunciado como \ (barra invertida) o ; (punto y coma).
// voy hacer primero el caso en el que los caracteres entre comillas no tienen
// espacios luego con espacio
//


void *check_fun(char *str)
{
  if (!str)
	return (NULL);
  return (str);
}

// set todo tipo de espacios
// example <echo"hello world"> 2>file | cat -e
int count_word(char *prompt, char *set, char *quotes, char *specials)
{
  int count;
  int size;

  size = 0;
  count = 0;
  (void)count;
  (void)quotes;
  (void)size;
  (void)set;
  while (*prompt)
  {
	if (*prompt && _find(specials, *prompt))//splecial
		printf("[%c]\n", *prompt++);
	else
		prompt++;
  }
  return (count);
}
// contempla el caso de que haya espacios entre comillas
char **split_token(char *prompt, char *set, char *specials, char *quotes)
{
  char **tmp;
  int word;
  int size;
  int count;

  count = 0;
  word = 0;
  (void)count;
  (void)word;
  (void)size;
  count = count_word(prompt, set, quotes, specials);
  tmp = NULL;
  return (tmp);
}
