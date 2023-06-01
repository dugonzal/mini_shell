/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:48:17 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/31 19:48:45 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int check_quotes_arr(char *str, char *quotes)
{
  char 	tmp;
  int 	j;
  int 	count;
  
  j = -1;
  count = 0;
  while (str[++j])
	if (search(quotes, str[j]))
	{
	  count++; 
	  tmp = str[j];
	  while (str[++j] && str[j] != tmp);
	  if (str[j] == tmp)
		count++;
	}
  if (count % 2 != 0)
	return (1);
  return (0);
}

int check_quotes(char **prompt, char *quotes)
{
  int	i;

  i = -1;
  while (prompt[++i])
	if (check_quotes_arr(prompt[i], quotes))
	  return (1);
  return (0);
}

int	check_pipe(char **prompt, char pipe)
{
  int size;
  int i;

  size = arr_size(prompt);
  if (prompt[0][0] == pipe || prompt[size - 1][0] == pipe)
	return (1);
  i = -1;
  while (++i < (size - 1))
	if (arr_size(prompt) > 1 &&  (prompt[i][0] == '>' || prompt[i][0] == '<') && prompt[i + 1][0] == '|')
		return (1);
	else if ((arr_size(prompt) > 1) && prompt[i][0] == pipe && prompt[i + 1][0] == pipe)
		return (1);
	else if (prompt[i] && prompt[i][0] == pipe && prompt[i][1] == pipe)
	  return (1);
  return (0);
}

int check_redir(char **prompt, char redir)
{
  int i;
  int size;

  size = arr_size(prompt);
  if (prompt[0] && prompt[size - 1][0] == redir)
	return (1);
  i = -1;
  while (prompt[++i])
	if (prompt[i] && prompt[i][0] == redir && prompt[i][2] == redir)
	  return (1);
	else if (arr_size(prompt) > 1 && prompt[i][0] == '|' \
	  && (prompt[i + 1][0] == '>' || prompt[i + 1][0] == '<'))
		return (1);
	else if (prompt[i] && i > 3 && prompt[size - 3][0] == redir \
	  && prompt[size - 2][0] != 0)
		return (1);
  return (0);
}

int check_semicolon(char **prompt)
{
	int i;

	i = -1;
	while (prompt[++i])
	if (prompt[i] && prompt[i][0] == ';' && prompt[i][1] == ';')
	  return (1);
	return (0);
}










