/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciclo <ciclo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 09:03:08 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/14 12:28:58 by ciclo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// voy a quitar las comilla y comprobar que hayan dos
//No interpretar comillas sin cerrar o caracteres especiales no especificados en el
//enunciado como \ (barra invertida) o ; (punto y coma).
// voy hacer primero el caso en el que los caracteres entre comillas no tienen
// espacios luego con espacios
int	verify_quotes(t_data *data)
{
	int i;
	int	err[2];

	err[1] = 0;
	err[0] = 0;
	i = 0;
	while (data->line[i] != 0)
	{
		if (data->line[i] == '\"')
			err[0]++;
		else if (data->line[i] == '\'')
			err[1]++;
		i++;
	}
	if (err[0] > 0 || err[1] > 0)
		data->quotes = 1;
	if (err[1] % 2 != 0 || err[0] % 2 != 0)
	{
		printf (RED"Error : Unmached quotes \n"RESET);
		return (1);
	}
	return (0);
}

void	parser(t_data *data)
{
	if (!data->line)
		return ;
	if (!ft_strncmp(data->line, "exit", 4))
	{
		ft_exit(data);
		return ;
	}
	else if (verify_quotes(data))
		return;
	if (data->quotes) // si hay comillas
	{
		data->bufer = ft_split(data->line, '\"');
	//	parser_quotes(data);
	}
	else // si no hay comillas
	{
		data->bufer = ft_split(data->line, ' ');
	//	parser_no_quotes(data);
	}

	bin_execute(data);
}
