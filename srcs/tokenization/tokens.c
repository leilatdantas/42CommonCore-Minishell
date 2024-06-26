/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:13:59 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/26 19:19:21 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token_type(char *token)
{
	if (token[0] == '|')
		return (PIPE);
	else if (token[0] == '>' && !search_char(">", token[1]))
		return (GREATER);
	else if (token[0] == '<' && !search_char("<", token[1]))
		return (LESSER);
	else if (token[0] == '>' && token[1] == '>')
		return (D_GREATER);
	else if (token[0] == '<' && token[1] == '<')
		return (D_LESSER);
	else if (token[0] == ' ')
		return (E_SPACE);
	else
		return (WORD);
}

void	get_token_state(t_token *token)
{
	char	*new_value;
	char	cmp;

	new_value = NULL;
	if (token->value[0] == '\'' || token->value[0] == '\"')
	{
		if (token->value[0] == '\"')
			token->state = IN_DQUOTES;
		else if (token->value[0] == '\'')
			token->state = IN_SQUOTES;
		cmp = token->value[0];
		new_value = ft_strtrim(token->value, &cmp);
		free(token->value);
		token->value = new_value;
	}
	else
		token->state = GENERAL;
}

/**
 * The function `end_word` sets the end index of a word in a given input string 
 * based on certain conditions.
 * 
 * @param sh A pointer to a structure named t_shell, which likely contains information about 
 * the shell environment and configuration.
 * @param input The `input` parameter in the `end_word` function is a character array or 
 * string that contains the input text being processed. 
 * It is used to determine the end of a word within the input text.
 */
void	end_word(t_shell *sh, char *input)
{
	sh->index->end = sh->index->start;
	if (input[sh->index->end] == '\"' || input[sh->index->end] == '\'')
		search_quote(input, &sh->index->end, input[sh->index->end]);
	else
		search_word(input, &sh->index->end);
}

/**
 * The function `fill_token_lst` parses input string and creates tokens based on whitespace 
 * and word boundaries.
 * 
 * @param sh The `sh` parameter is a pointer to a `t_shell` struct, which likely contains 
 * information and settings related to the shell environment.
 * @param input The `fill_token_lst` function takes a `t_shell` structure pointer `sh` and a 
 * character pointer `input` as parameters. The function processes the input string character by 
 * character to create tokens and add them to a linked list `token_lst` within the `t_shell` structure.
 */
void	fill_token_lst(t_shell *sh, char *input)
{
	t_token	*node_content;

	while (input[sh->index->start])
	{
		node_content = ft_calloc(1, sizeof(t_token));
		if (!node_content)
			clear_exit(sh, 1);
		if (ft_iswhitespace(input[sh->index->start]))
		{
			node_content->value = ft_strdup(" ");
			while (ft_iswhitespace(input[sh->index->start]))
				sh->index->start++;
		}
		else
		{
			end_word(sh, input);
			node_content->value = ft_substr(input, sh->index->start,
					sh->index->end - sh->index->start);
			sh->index->start = sh->index->end;
		}
		node_content->type = get_token_type(node_content->value);
		get_token_state(node_content);
		ft_lstadd_back(&sh->token_lst, ft_lstnew(node_content));
		node_content->pos = sh->index->pos++;
	}
}
