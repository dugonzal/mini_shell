/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:52:34 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/04/30 15:22:16 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*fun_check(char *str)
{
  if (!str)
	  return (NULL);
  return (str);
}

int	specials_token(char *prompt)
{
  int	i;

  if (!(*prompt == 0) && !(ft_strlen(prompt) > 1))
	  return (1);
  i = 0;
  while (prompt[i] == prompt[i + 1])
	i++;
  return (++i); 
}

int	caracteres_token(char *prompt, char *set, char *quotes, char *specials)
{
  int i;
  
  i = 0;
  while (prompt[i] && !search(set, prompt[i])
  && !search(quotes, prompt[i]) && !search(specials, prompt[i]))
	i++;
  return (i);
}

int quotes_token(char *str, char quote)
{
  int i;

  if (*str == quote)
	i = 1;
  else
	return (0);
  while (str[i] && str[i] != (quote))
    i++;
  if (str[i] == quote)
    i++;
  return (i);
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
	if (*tmp && search(specials, *tmp))
	{
	  tmp += specials_token(tmp);
	  count++;
	}
	else if (*tmp && !search(specials, *tmp)
	&& !search(quotes, *tmp) && !search(set, *tmp))
	{
		tmp += caracteres_token(tmp, set, quotes, specials);
		count++;
	}
	else if (*tmp && search(quotes, *tmp))
	{
	  tmp += quotes_token(tmp, *tmp);
	  count++;
	}
	else
		tmp++;
  }
  return (count);
}

