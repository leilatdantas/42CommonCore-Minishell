/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:14:55 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/26 19:49:18 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function `read_and_join_input` reads user input, trims whitespace, joins it with existing input, and returns the result.
 * 
 * @param join The `join` parameter is a pointer to a character array that is used to store the 
 * concatenated input strings. The function reads a new input string, trims any leading or 
 * trailing whitespace characters, concatenates it with the existing `join` string.
 * @return The function `read_and_join_input` is returning the `join` 
 * variable after reading input from the user, trimming whitespace, 
 * and joining the input with the existing `join` string.
 */
char	*read_and_join_input(char *join)
{
	char	*ret;

	ret = readline("> ");
	if (!ret)
		return (free(join), NULL);
	ret = ft_strtrim_mod(ret, " \t");
	join = ft_strjoin_mod(join, ret);
	free(ret);
	join = ft_strtrim_mod(join, " \t");
	return (join);
}

char	*open_pipe(t_shell *sh, char *input)
{
	char	*join;

	join = ft_strdup(input);
	while (1)
	{
		join = read_and_join_input(join);
		if (!join)
			return (NULL);
		if (join[ft_strlen(join) - 1] != '|'
			|| join[ft_strlen(join) - 2] == '|')
			break ;
		if (!sintax_validation(join))
		{
			add_history(join);
			free(join);
			free(input);
			reinit_shell(sh);
			sh_loop(sh);
		}
	}
	return (join);
}

/**
 * The function `handle_input` trims the input, validates its syntax, and either opens a pipe or duplicates the trimmed input.
 * 
 * @param sh t_shell structure which contains information about the shell environment and configuration
 * @param input The `handle_input` function takes a pointer to a `t_shell` struct and a character pointer `input` as parameters. 
 * The function first trims the input by removing leading and trailing whitespace characters and tabs using the `ft_strtrim` function.
 * 
 * @return The function `handle_input` returns a `char*` value, which can be either `NULL` or a pointer to a string.
 */
char	*handle_input(t_shell *sh, char *input)
{
	char	*trimmed_input;
	char	*ret;

	ret = NULL;
	trimmed_input = ft_strtrim(input, "\t ");
	if (!trimmed_input || !*trimmed_input || !sintax_validation(trimmed_input))
	{
		add_history(input);
		free(input);
		if (trimmed_input)
			free(trimmed_input);
		sh_loop(sh);
	}
	else if (trimmed_input[ft_strlen(trimmed_input) - 1] == '|')
		ret = open_pipe(sh, trimmed_input);
	else
		ret = ft_strdup(trimmed_input);
	free(input);
	if (trimmed_input)
		free(trimmed_input);
	return (ret);
}

char	*get_line(t_shell *sh)
{
	char	*input;

	input = readline(PROMPT);
	if (!input)
	{
		write(1, "exit\n", 5);
		rl_clear_history();
		clear_exit(sh, g_signo);
	}
	return (handle_input(sh, input));
}

char	*get_path_aux(char **envp)
{
	int		i;
	char	*path_aux;

	i = 0;
	path_aux = NULL;
	while (envp[i] && (ft_strncmp(envp[i], "PATH=", 5) != 0))
		i++;
	if (envp[i] && envp[i][5] != '\0')
		path_aux = ft_strdup(envp[i] + 5);
	return (path_aux);
}
