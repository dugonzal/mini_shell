/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 09:03:08 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/30 12:52:46 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// voy a quitar las comilla y comprobar que hayan dos
//No interpretar comillas sin cerrar o caracteres especiales no especificados en el
//enunciado como \ (barra invertida) o ; (punto y coma).
// voy hacer primero el caso en el que los caracteres entre comillas no tienen
// espacios luego con espacio

char *fun_check(char *str)
{
  if (!str)
	return (NULL);
  return (str);
}

int specials_token(char *prompt)
{
  int i;

  if (!(*prompt == 0) && !(ft_strlen(prompt) > 1)) // si en la cadena solo hay un token retorno 1
	  return (1);
  i = 0;
  while (prompt[i] == prompt[i + 1]) // cuento hasta que no hayan tokens iguales
	  i++;
  return (++i);// cuento el primer token 
}

int	caracteres_token(char *prompt, char *set, char *quotes, char *specials)
{
  int i;
  
  i = 0;
  while (prompt[i] && !_find(set, prompt[i])
  && !_find(quotes, prompt[i]) && !_find(specials, prompt[i]))
	i++;
  return (i);
}

int quotes_token(char *str)
{
  int i;
  char quote;

  i = 1;
  quote = *str;
  while (str[i] && str[i] != (quote))
    i++;
  if (str[i] == quote)
    return (++i);
  return (0);
}
// set todo tipo de espacios
// example <echo"hello world"> 2>file | cat -e
int count_word(char *prompt, char *set, char *quotes, char *specials)
{
  int count;
  char *tmp;

  count = 0;
  tmp = prompt;
  while (*tmp)
  {
	if (*tmp && _find(specials, *tmp))//special
	{
	  tmp += specials_token(tmp); // paso como parametro desde ese punto de la cadena
	  count++;
	}
	else if (*tmp  && !_find(specials, *tmp) // caracteres
	&& !_find(quotes, *tmp) && !_find(set, *tmp)) 
	{
		tmp += caracteres_token(tmp, set, quotes, specials);
		count++;
	}
	else if (*tmp && _find(quotes, *tmp))
	{
	  tmp += quotes_token(tmp);
	  count++;
	}
	else // estos son los espacios
		tmp++;
  }
  return (count);
}

char **split_token(char *prompt, char *set, char *specials, char *quotes)
{
  char **tmp;
  int word;
  int size;

  word = 0;
  fun_check(*(tmp = (char **)malloc(sizeof(char *) \
  * count_word(prompt, set, quotes, specials) + 1)));
  while (*prompt)
  {
	size = 0;
	if (*prompt && _find(specials, *prompt)) // specials_token
	{
		size = specials_token(prompt);
		tmp[word] = fun_check(ft_strndup(prompt, size));
		word++;
	}
	else if (*prompt && !_find(specials, *prompt) // caracteres_token
	&& !_find(quotes, *prompt) && !_find(set, *prompt))
	{
	  size = caracteres_token(prompt, set, quotes, specials);
	  tmp[word] = fun_check(ft_strndup(prompt, size));
	  word++;
	}
	else if (*prompt && _find(quotes, *prompt))
	{
	  size = quotes_token(prompt);
	  tmp[word] = fun_check(ft_strndup(prompt, size));
	  word++;
	}
	else
		prompt++;
	prompt += size;
  }
  tmp[word] = NULL;
  return (tmp);
}
