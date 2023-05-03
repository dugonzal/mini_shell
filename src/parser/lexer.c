/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:58:25 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/03 16:58:56 by Dugonzal         ###   ########.fr       */
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

int count_expanser(char *str)
{
  int i;

  i = 0;
  while (str[i] && ft_isalpha(str[i]))
	i++;
  return (i);
}

char *expanser_check(char *str)
{
  int	i;
  char	*tmp;
  char *tmp2;
  char *str_tmp;
  i = -1;
  while (str[++i])
	if (str[i] && str[i] == '$' && ft_isalpha(str[i + 1]))
	{
	  tmp = ft_strndup(&str[i + 1], count_expanser(&str[i + 1]));
	  if (getenv(tmp))
	  {
		tmp2 = ft_strdup(getenv(tmp));
		str_tmp = ft_strndup(str, i);
		str_tmp = ft_strjoin(str_tmp, tmp2, 1);
		i = ft_strlen(str_tmp);
		str_tmp = ft_strjoin(str_tmp, &str[i], 1);
		free (tmp);
		free (tmp2);
		return (str_tmp);
	  }
	  else
	  {
		free (tmp);
		err_msg(RED"Error: variable '$' undefine "RESET);
		return (NULL);	
	  }
	}
  return (NULL);
}

int	expanser(t_data *data)
{
  int i;
  char *tmp;

  tmp = NULL;
  i = -1;
  while (data->bufer[++i])
	if (data->bufer[i] && search(data->bufer[i], '$'))
	{
		if (!expanser_check(data->bufer[i]))
			return (1);
		else
		  tmp = expanser_check(data->bufer[i]);
	}
  if (tmp)
  {
	free (data->bufer[i]); 
	data->bufer[i] = ft_strdup(tmp);
	free (tmp);
  }
  return (0);
}

int	lexer(t_data *data)
{
  if (!data->line[0] || !ft_strlen(data->line))
	return (1);
  data->line = ft_strtrim(data->line, " \t\v\f\r", 1);
  data->bufer = split_token(data->line, " \t\v\f\r", ">|<", "\"\'");
  if (!data->bufer)
	  return (1);
  else if (lexer_errors(data))
    return (1);
  if (expanser(data))
	return (1);
 // print (data->bufer);
  add_history (data->line);
  free (data->line);
  return (0);
}


