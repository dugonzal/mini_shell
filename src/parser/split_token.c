/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 09:03:08 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/30 10:46:36 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// voy a quitar las comilla y comprobar que hayan dos
//No interpretar comillas sin cerrar o caracteres especiales no especificados en el
//enunciado como \ (barra invertida) o ; (punto y coma).
// voy hacer primero el caso en el que los caracteres entre comillas no tienen
// espacios luego con espacio
//


void *fun_check(char *str)
{
  if (!str)
	return (NULL);
  return (str);
}

int splecial_token_count(char *prompt)
{
  int i;

  if (!(ft_strlen(prompt) > 1))
	  return (1);
  i = 0;
  while (prompt[i] == prompt[i + 1])
	  i++;
  return (++i);
}

// set todo tipo de espacios
// example <echo"hello world"> 2>file | cat -e
int count_word(char *prompt, char *set, char *quotes, char *specials)
{
  int count;
  int size;

  size = 0;
  count = 0;
  (void)quotes;
  (void)size;
  (void)set;
  while (*prompt)
  {
	if (*prompt && _find(specials, *prompt))//splecial
	{
	  prompt += splecial_token_count(&*prompt);
	  count++;
	}
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
  printf ("%d", count);
  tmp = NULL;
  return (tmp);
}
