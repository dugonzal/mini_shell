/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:58:25 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/05 11:06:25 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	lexer_errors(char **str)
{
	if (check_quotes(str, "\'\""))
		return (err_msg(RED"minishell: syntax error quotes \" <-> \'"RESET));
	else if (check_pipe(str, '|'))
		return (err_msg(RED"minishell: syntax error pipe '|'"RESET));
	else if (check_redir(str, '<'))
		return (err_msg(RED"minishell: syntax error redir '<'"RESET));
	else if (check_redir(str, '>'))
		return (err_msg(RED"minishell: syntax error redir '>'"RESET));
	else if (check_semicolon(str))
		return (err_msg(RED"minishell: syntax error parse near ';;' "RESET));
	return (0);
}

int	lexer(t_data *data)
{
	if (!data->line[0])
		return (1);
	data->line = ft_strtrim(data->line, " \t\v\f\r", 1);
	if (!ft_strlen(data->line))
		return (1);
	data->bufer = split_token(data->line, " \t\v\f\r", ">|<;", "\"\'");
	if (!data->bufer[0])
	{
		data->status = 1;
		free (data->line);
		return (1);
	}
	if (lexer_errors(data->bufer) || expanser(data) || expanser_env(data))
	{
		free (data->line);
		free_array(data->bufer);
		data->status = 1;
		return (1);
	}
	add_history (data->line);
	free (data->line);
	return (0);
}
