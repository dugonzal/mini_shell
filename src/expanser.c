/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:03:30 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/05 09:57:08 by Dugonzal         ###   ########.fr       */
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

void	expandir(t_data *data, int i, int j)
{
	char	*env;

	j++;
	env = ft_itoa(data->status);
	if (j > 1)
		env = ft_strjoin(ft_strndup(data->bufer[i], j - 1), env, 1);
	if (data->bufer[i][j + 1])
		env = ft_strjoin(env, &data->bufer[i][j + 1], 1);
	free (data->bufer[i]);
	data->bufer[i] = env;
}

int	expandir_env(t_data *data, int i, int j)
{
	char	*env;
	int		size;

	size = count_expanser(&data->bufer[i][++j]);
	env = ft_getenv_builtins(ft_strndup(&data->bufer[i][j], size), data->env);
	if (!env)
		return (err_msg(RED"Error: Environment variable not found."RESET));
	if (data->bufer[i][j + size] != 0)
		env = ft_strjoin(env, &data->bufer[i][j + size], 1);
	free (data->bufer[i]);
	data->bufer[i] = env;
	return (0);
}

int	expanser_env(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (data->bufer[++i])
	{
		if (data->bufer[i] && ft_strlen(data->bufer[i]) > 1 \
		&& search(data->bufer[i], '$') && !search(data->bufer[i], '\''))
		{
			j = find_caracter(data->bufer[i], '$');
			if (expandir_env(data, i, j))
				return (1);
			if (search(data->bufer[i], '$'))
				expanser_env (data);
		}
	}
	return (0);
}

int	expanser(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (data->bufer[++i])
	{
		if (data->bufer[i] && ft_strlen(data->bufer[i]) > 1 \
		&& search(data->bufer[i], '$') && !search(data->bufer[i], '\''))
		{
			j = find_caracter(data->bufer[i], '$');
			if (data->bufer[i][j + 1] == '?')
			{
				expandir(data, i, j);
				if (search(data->bufer[i], '$'))
					expanser(data);
			}
		}
	}
	if (expanser_env(data))
		return (1);
	return (0);
}
