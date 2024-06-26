/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:20:33 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/26 19:20:38 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_char(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

void	search_quote(char *input, int *j, char c)
{
	(*j)++;
	while (input[*j] != c && input[*j])
		(*j)++;
	if (input[*j] == c)
		(*j)++;
}

/**
 * The function `search_word` processes input characters until it reaches specific delimiters or whitespace.
 * 
 * @param input The `input` parameter is a pointer to a character array or string, and the `end` 
 * parameter is a pointer to an integer that represents the current position within the string 
 * being searched. The `search_word` function is designed to search for specific characters or 
 * patterns within the input string based on certain
 * @param end The `end` parameter in the `search_word` function is a pointer to an integer. 
 * It is used to keep track of the current position in the `input` string being processed. 
 * The function examines characters in the `input` string starting from the position indicated 
 * by `end` and updates `
 * @return The function `search_word` does not have a return value.
 * The function appears to be designed to search for specific characters or patterns 
 * within a given input string and update the `end` index accordingly.
 */
void	search_word(char *input, int *end)
{
	if (input[*end] && search_char("<>|$", input[*end])
		&& !search_char("\"\'", input[*end]))
	{
		if (input[*end] == '$' || input[*end] == '|')
		{
			(*end)++;
			return ;
		}
		while (input[*end] && search_char("<>", input[*end])
			&& !search_char("|$\"\'", input[*end]))
			(*end)++;
		return ;
	}
	if (input[*end] && search_char("\"\'", input[*end]))
		search_quote(input, end, input[*end]);
	else
	{
		while (input[*end] && !search_char("\"\'", input[*end])
			&& !search_char("<>$|", input[*end])
			&& !ft_iswhitespace(input[*end]))
			(*end)++;
	}
}
