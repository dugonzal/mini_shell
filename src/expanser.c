/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:03:30 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/03 20:06:33 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int count_expanser(char *str)
{
  int i;

  i = 0;
  while (str[i] && ft_isalpha(str[i]))
	i++;
  return (i);
}

char *ft_getenv(char *str)
{
  if (!str)
	return (NULL);
  if (getenv(str))
	return (getenv(str));
  return (NULL);
}
// "'hola '$USER' que tal'"
// antes de la expansion -> durante la expansion -> despues de la expansion
int	expanser(t_data *data)
{
  int	i;
  int	j;
  char	*full;
  i = -1;
  if (!data->bufer)
	return (0);
  while (data->bufer[++i])
	if (data->bufer[i] && search(data->bufer[i], '$'))
	{
	  j = 0;
	  while (data->bufer[i][j] != '$')
		  j++;
	  if (data->bufer[i][j] == '$' && ft_isalpha(data->bufer[i][j + 1]))
	  {
		full = ft_strjoin(ft_strndup(&data->bufer[i][j - 1], j), ft_getenv(strndup(&data->bufer[i][j + 1], count_expanser(&data->bufer[i][j + 1]))), 0); // guardo la expansion
		printf ("----%s---\n", full);
		  //if (data->bufer[i][j + count_expanser(&data->bufer[i][j + 1])] != 0) // si hay algo despues de la expansion
		 // char *tmp1 = ft_strdup(&data->bufer[i][j + count_expanser(&data->bufer[i][j + 1])]); // guardo lo que hay despues de la expansion
		//full = ft_strjoin(full, tmp1, 1); // concateno lo que hay antes de la expansion con la expansion y lo que hay despues de la expansion
		printf ("----%s---\n", full);
		//if (search(data->bufer[i], '$'))
		//  expanser(data);
	  }
	  else if (data->bufer[i][j + 1] != ft_isalpha(data->bufer[i][j + 1]))
		continue ;
	  // estoy en el array de la expansion
	}
  return (0);
}


