/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:03:30 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/03 20:53:30 by Dugonzal         ###   ########.fr       */
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

int	expanser(t_data *data)
{
  int	i;
  int	j;
  char	*env;
  int	size;
  
  i = -1;
  if (!data->bufer)
	return (0);
  while (data->bufer[++i])
	if (data->bufer[i] && search(data->bufer[i], '$'))
	{
	  j = 1;
	  while (data->bufer[i][j] != '$')
		  j++;
	  if (data->bufer[i][j] == '$' && ft_isalpha(data->bufer[i][j + 1]))
	  {
		j++;
		size = count_expanser(&data->bufer[i][j]);
		env = ft_getenv(strndup(&data->bufer[i][j], size)); // expanser
		if (!env)
		{
		  err_msg(RED"Error: Environment variable not found."RESET);
		  return (1);
		}
		if (j > 1)
			env = ft_strjoin(strndup(data->bufer[i], j - 1), env, 1);
		if (data->bufer[i][j + size] != 0)
			env = ft_strjoin(env, &data->bufer[i][j + size], 1);
		free(data->bufer[i]);
		data->bufer[i] = env;
		if (search(data->bufer[i], '$'))
		  expanser(data);
	  }
	  else if (data->bufer[i][j + 1] != ft_isalpha(data->bufer[i][j + 1]))
		continue ;
	}
  return (0);
}


