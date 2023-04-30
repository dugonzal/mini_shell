/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:36:28 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/04/29 12:57:59 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
  char *tmp;
  int i;

  i = 0;
  tmp = str;
  if (_find("<|>", *tmp))
  {
    while (tmp[i] && _find("<|>", tmp[i]))
      i++;
    printf ("i = [%d]\n", i);
    return (i);
  }
  while (tmp[i] && !_find(set, tmp[i]) \
  && !_find("\'\"", tmp[i]) && !_find("<|>", tmp[i]))
	  i++;
  return (i);
}

int count_row_quotes(char *str)
{
  int i;
  char quote;

  if (str[0] != '\'' && str[0] != '\"')
    return (0);
  i = 1;
  quote = *str;
  while (str[i] && str[i] != (quote))
    i++;
  if (str[i] == quote)
    return (i + 1);
  return (0);
}
