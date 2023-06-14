/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:03:30 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/14 08:35:11 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expandir_status(t_data *data, int i, int j)
{
	char	*env;

	env = ft_itoa(g_status);
	if (j > 1)
		env = ft_strjoin(ft_strndup(data->bufer[i], j - 1), env, 1);
	if (data->bufer[i][j + 1])
		env = ft_strjoin(env, &data->bufer[i][j + 1], 1);
	free (data->bufer[i]);
	data->bufer[i] = env;
}

char	*get_env(char *str, char **env)
{
	int		i;
	char	*expanser;
	char	*tmp;
	int		size;

	i = -1;
	tmp = tmp_variable(str);
	size = find_caracter(tmp, '=');
	while (env[++i])
	{
		if (!ft_strncmp(env[i], tmp, size) && env[i][size] == '=')
		{
			expanser = ft_strdup(&env[i][size + 1]);
			if (search(str, '/'))
			{
				free (tmp);
				return (return_expanser(str, \
				ft_strjoin(expanser, &str[size], 1)));
			}
			return (return_expanser(tmp, expanser));
		}
	}
	if (search (str, '/'))
		free (tmp);
	return (return_expanser(str, ft_strdup(&str[size])));
}

void	expandir_env(t_data *data, int i, int j)
{
	int		size;
	char	*tmp;

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

void	expanser(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (data->bufer[++i])
	{
		j = -1;
		while (data->bufer[i][++j])
		{
			if (data->bufer[i][j] == '$' && data->bufer[i][j + 1] == '?' \
				&& !search(data->bufer[i], '\''))
				expandir_status(data, i, ++j);
			else if (data->bufer[i][j] == '$' && data->bufer[i][j + 1] \
				&& !search(data->bufer[i], '\''))
			{
				expandir_env(data, i, j);
				if (search(data->bufer[i], '$'))
					i -= 1;
				break ;
			}
		}
	}
}
