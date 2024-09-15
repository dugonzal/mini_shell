/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:26:30 by ciclo             #+#    #+#             */
/*   Updated: 2024/09/15 12:44:51 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*prompt(char **env)
{
	char	*prompt;
	char	*user;
	char	*host;

	user = ft_getenv_builtins("USER", env);
	if (!user)
		user = ft_strdup("Anonimo");
	user[0] = ft_toupper(user[0]);
	user = ft_strjoin("\033[1;31m", user, 0);
	host = ft_strjoin("\033[1;34m@MiniShell\033[0m", "🙂🚀❯ ", 0);
	prompt = ft_strjoin(user, host, 1);
	free (host);
	return (prompt);
}

void	*free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free (array);
	return (NULL);
}

void	print(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		ft_printf ("[%s] ", str[i]);
	ft_printf ("\n");
}

int	search(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

int	err_msg(char *str)
{
	if (str)
		ft_putendl_fd(str, 2);
	return (1);
}

void	get_env_and_path(t_data *data, char **env)
{
	int		i;

	data->env = ft_calloc(arr_size(env) + 1, sizeof(char *));
	if (!data->env)
		err(RED"minishell: malloc error"RESET);
	i = -1;
	while (env[++i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
		{
			free_array(data->env);
			err(RED"minishell: malloc error"RESET);
		}
	}
	data->env[i] = NULL;
}


