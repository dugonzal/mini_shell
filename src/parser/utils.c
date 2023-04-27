/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:36:28 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/04/27 14:36:31 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int _count_row(char *str, char *set)
{
  int i;
 
  i = 1;
  while (str[i] && !_find(set, str[i]))
	i++;
  return (i);
}

int count_row_quotes(char *str)
{
  int i;
  char quote;
  
  i = 1;
  quote = *str;
  while (str[i] && str[i] != quote)
	i++;
  if (str[i] && _find("\'\"", str[i]))
	i++;
  return (i);
}


