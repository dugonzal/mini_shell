/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:58:25 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/04 19:52:47 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int lexer_errors(t_data *data)
{
  if (check_quotes(data->bufer, "\'\""))
	return(err_msg(RED"minishell: syntax error quotes \" <-> \'"RESET));
  else if (check_pipe(data->bufer, '|'))
	return(err_msg(RED"minishell: syntax error pipe '|'"RESET));
  else if (check_redir(data->bufer, '<'))
	return (err_msg(RED"minishell: syntax error redir '<'"RESET));
  else if (check_redir(data->bufer, '>'))
	return (err_msg(RED"minishell: syntax error redir '>'"RESET));
  return (0);
}

int	lexer(t_data *data)
{
  if (!data->line[0])
	return (1);
  data->line = ft_strtrim(data->line, " \t\v\f\r", 1);
  if (ft_strlen(data->line) > 1 && search("\'\"", data->line[0]) \
	&& search("\'\"", data->line[ft_strlen(data->line) - 1]))
	data->line = ft_strtrim(data->line, "\'\"", 1);
  if (!data->line[0] || !ft_strlen(data->line))
	return (1);
  data->bufer = split_token(data->line, " \t\v\f\r", ">|<;", "\"\'");
  if (!data->bufer)
  {
	free (data->line);
	return (1);
  }
  else if (lexer_errors(data) || expanser(data))
  {
	free (data->line);
	free_array(data->bufer);
    return (1);
  }
  add_history (data->line);
  free (data->line);
  return (0);
}


