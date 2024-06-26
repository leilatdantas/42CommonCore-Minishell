/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:54:33 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/26 19:14:17 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_tokens(t_shell *sh)
// {
// 	t_token	*token_content;
// 	t_list	*tmp;
// 	char	*type[] = {YELLOW "WORD" COLOR_RESET, RED "PIPE" COLOR_RESET,
// RED "GREATER" COLOR_RESET, RED "LESSER" COLOR_RESET, RED "D_GREATER"
// COLOR_RESET, RED "D_LESSER" COLOR_RESET, LIGHTBLUE "E_SPACE" COLOR_RESET,
// LIGHTGREEN"APPEND" COLOR_RESET, LIGHTGREEN "OUTFILE" COLOR_RESET, LIGHTGREEN
// "INFILE"COLOR_RESET, LIGHTGREEN"HEREDOC" COLOR_RESET};
// 	char	*state[] = {PINK"GENERAL"COLOR_RESET,
// PURPLE"IN_DQUOTES"COLOR_RESET, LIGHTPURPLE"IN_SQUOTES" COLOR_RESET};
// 	char	*expand[] = {"EXPANDE", "NAO_EXPANDE"};

// 	tmp = sh->token_lst;
// 	while (tmp)
// 	{
// 		token_content = tmp->content;
// 		printf("Token %02d: ", token_content->pos);
// 		printf(BLUE_BG"%s"COLOR_RESET, token_content->value);
// 		printf("\nType: %s\nState: %s\n", type[token_content->type],
// 			state[token_content->state]);
// 		if (token_content->type == HEREDOC)
// 			printf("Type of heredoc: %d %s\n",
// 				token_content->not_expand, expand[token_content->not_expand]);
// 		tmp = tmp->next;
// 	}
// }

void	print_arrays(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		ft_putstr_fd(paths[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

/**
 * The function `print_env` iterates through a linked list of environment variables and prints out the
 * key-value pairs for visibl Invalid color format. Use #RGB, #RGBA, #RRGGBB or #RRGGBBAA.e variables.
 * 
 * @param sh The `print_env` function takes a pointer to a `t_shell` struct as a parameter. This struct
 * likely contains information related to the shell environment, such as a linked list (`env_lst`) of
 * environment variables (`t_env`). The function iterates through the linked list and prints out the
 * key
 */
void	print_env(t_shell *sh)
{
	t_env	*env_content;
	t_list	*tmp;

	tmp = sh->env_lst;
	while (tmp)
	{
		env_content = tmp->content;
		if (env_content->visible == true && env_content->value)
			printf("%s=%s\n", env_content->key, env_content->value);
		tmp = tmp->next;
	}
}
