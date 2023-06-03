/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:52:25 by sizquier          #+#    #+#             */
/*   Updated: 2023/06/03 09:35:01 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_invalid(char *c)
{
	ft_printf(RED"export: `%s': not a valid identifier\n"RESET, c);
	return ;
}

int	ft_cmd_isalnum(char	*str)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '=')
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	return (1);
}



