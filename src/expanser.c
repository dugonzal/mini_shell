/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:03:30 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/09 19:32:37 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_caracter(char *str, char c)
{
	int	j;

	j = 0;
	while (str[j] != c)
		j++;
	return (j);
}

int	count_expanser(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && !search(" \t\v\f\r\"\'", str[i]) && 	str[i] != '$')
		;
	return (i);
}
void	expandir_status(t_data *data, int i, int j)
{
	char	*env;

	j++;
	env = ft_itoa(data->status);
	if (j > 1)
		env = ft_strjoin(ft_strndup(data->bufer[i], j - 1), env, 1);
	if (data->bufer[i][j + 1] != 0)
		env = ft_strjoin(env, &data->bufer[i][j + 1], 1);
	free (data->bufer[i]);
	data->bufer[i] = env;
}

char	*get_env(char *str, char **env)
{
	int		i;
	int		count;
	i = -1;
	
	while (env[++i])
	{
	  if (!ft_strncmp(str, env[i], find_caracter(env[i], '=')))
	  {
		if (search(str, '\'))
		{
			count = find_caracter(str, '\');
			return (ft_strjoin(ft_strndup(), , 1));
		}

		  free (str);
		  return (ft_strdup(&env[i][find_caracter(env[i], '=') + 1]));
	  }
	}
	return (ft_strdup(""));
}

int	expanser(t_data *data)
{
	int		i;
	int		j;
	char 	*tmp;
	int		size;
	i = -1;
	while (data->bufer[++i])
	{
	  j = -1;
	  while (data->bufer[i][++j])
	  {
		if (data->bufer[i][j] == '$' && data->bufer[i][j + 1] == '?')
		  expandir_status(data, i, j);
		else if (data->bufer[i][j] == '$' && data->bufer[i][j + 1])
		{
		  size = count_expanser(&data->bufer[i][j + 1]);
		  tmp = ft_strndup(&data->bufer[i][j + 1], size);
		  tmp = get_env(tmp, data->env);
		  if (j)
			tmp = ft_strjoin(ft_strndup(data->bufer[i], j), tmp, 1);
		  if (data->bufer[i][j + size + 1])
			tmp = ft_strjoin(tmp, &data->bufer[i][j + size + 1], 1);
		  free (data->bufer[i]);
		  data->bufer[i] = tmp;
		}
	  }
	}
	return (0);
}
