/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 12:00:03 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/11 12:41:32 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_tmp(char *str, char *tmp)
{
  if (str)
	  free (str);
  if (tmp)
	  free (tmp);
}

char *return_expanser(char *tmp, char *expanser)
{
  free (tmp);
  return (expanser);
}

int	find_caracter(char *str, char c)
{
	int	j;

	j = -1;
	while (str[++j] && str[j] != c)
		;
	return (j);
}

int	count_expanser(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && !search(" \t\v\f\r\"\'", str[i]) \
	  && str[i] != '$')
		;
	return (i);
}

char *tmp_variable(char *str)
{
  char *tmp;

	if (search(str, '/'))
		tmp = ft_strndup(str, find_caracter(str, '/'));
	else
		tmp = str;
	return  (tmp);
}
