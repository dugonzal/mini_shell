/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:58:25 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/04/30 11:27:41 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//analizar los tokens y divida aquellos que se unieron. Podrías verificar\
//si hay caracteres de redirección o tuberías entre dos tokens, y si los hay, dividir el token en dos.

/// si se ponen los carac
int	lexer(t_data *data)
{
  if (data->line[0] == '\0' || !ft_strlen(data->line))
	return (1);
  data->line = ft_strtrim(data->line, " \t\v\f\r", 1);
  if (!(data->bufer = split_token(data->line, " \t\v\f\r", ">|<", "\"\'")))
	return (1);
  write (1, "\n\n", 2);
 // prin (data->bufer);
  // antes de analizar tengo que recorrer el array en busca de los caracteres especiales que esten juntos a un token
 // data->pipe = check_pipe(data->bufer, '|');
 // data->redir = check_redir(data->bufer, '>');
 // parse_tokens(data->bufer);
  //if (data->pipe == 2)
//	return (1);
  print (data->bufer);
  add_history (data->line);
 // free (data->line);
  return (0);
}


