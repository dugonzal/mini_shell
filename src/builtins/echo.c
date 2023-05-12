/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:42:28 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/12 11:54:14 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo_builtin(t_cmd *cmd)
{
	char	*flag_n; // para la variable -n
	int		num_arg; // para controlar los argumentos que recibimos
	int		i;

	num_arg = 1;
	flag_n = 0;
	i = 0;
	/*caso uso, Mientras la primera coincidencia en el str que numero de argumentos de -n, en */
	while (cmd->cmd[num_arg] && ft_strncmp(cmd->cmd[num_arg], "-n", 2) == 0)
	{
		i = 1;
		flag_n = cmd->cmd[num_arg];
		if (flag_n && ft_strncmp(flag_n, "-n", 2) == 0)
			while (flag_n[i] == 'n') // da igual cuantas n se encuentren, sólo interpreta la primera
				i++;
		if (flag_n && !flag_n[i])
			num_arg++;
		else
			break ;
	}
	ft_execute_echo(cmd->cmd + num_arg); //sino exite -n detrás de echo-> salto de linea
	if (!flag_n || (flag_n && flag_n[i] != '\0'))
		write(1, "\n", 1);
}

void	ft_execute_echo(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
}
