/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:52:34 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/26 23:50:56 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*fun_check(char *str)
{
	if (!str)
		return (NULL);
	return (str);
}

int	specials_token(const char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] == prompt[i + 1])
		i++;
	return (i + 1);
}

int	caracteres_token(const char *prompt, char *set, char *quote, char *specials)
{
	int	i;

	i = 0;
	while (prompt[i] && !search(set, prompt[i])
		&& !search(quote, prompt[i]) && !search(specials, prompt[i]))
		i++;
	if (search (quote, prompt[i]))
		i += quotes_token(prompt + i, prompt[i], set);
	return (i);
}

int	quotes_token(const char *str, char quote, char *set)
{
	int	i;

	if (*str == quote)
		i = 1;
	else
	  return (0);
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	while (str[i] && !search(set, str[i]))
	  i++;
	if (search("\'\"", str[i]))
		i += quotes_token(str + i, str[i], set);
	return (i);
}

int	count_tokens(const char *prompt, char *set, char *quotes, char *specials)
{
	char	*tmp;
	int		count;
	
	count = 0;
	tmp = (char *)prompt;
	while (*tmp)
	{
		if (*tmp && search(specials, *tmp))
			tmp += specials_token(tmp);
		else if (*tmp && !search(specials, *tmp) \
		&& !search(quotes, *tmp) && !search(set, *tmp))
			tmp += caracteres_token(tmp, set, quotes, specials);
		else if (*tmp && search(quotes, *tmp))
			tmp += quotes_token(tmp, *tmp, set);
		while (*tmp && search(set, *tmp))
			tmp++;
		count++;
	}
	return (count);
}
