/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:03:30 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/03 20:24:43 by Dugonzal         ###   ########.fr       */
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
  char *env;
  char	*full;
  i = -1;
  if (!data->bufer)
	return (0);
  (void)full;
  while (data->bufer[++i])
	if (data->bufer[i] && search(data->bufer[i], '$'))
	{
	  j = 0;
	  while (data->bufer[i][j] != '$')
		  j++;
	  if (data->bufer[i][j] == '$' && ft_isalpha(data->bufer[i][j + 1]))
	  {
		env = ft_getenv(strndup(&data->bufer[i][j + 1], count_expanser(&data->bufer[i][j + 1]))); // expanser
		if (j > 1)
			env = ft_strjoin(strndup(data->bufer[i], j), env, 0);
		if (data->bufer[i][j + count_expanser(&data->bufer[i][j + 1])] != 0)
			env = ft_strjoin(env, &data->bufer[i][j + count_expanser(&data->bufer[i][j + 1])], 0);
		free(data->bufer[i]);
		data->bufer[i] = env;
		if (search(data->bufer[i], '$'))
		  expanser(data);
	  }
	  else if (data->bufer[i][j + 1] != ft_isalpha(data->bufer[i][j + 1]))
		continue ;
	  // estoy en el array de la expansion
	}
  return (0);
}


