/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:06:07 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/26 19:17:51 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function `reinit_shell` resets a shell structure by freeing memory, 
 * zeroing out an index, and setting the number of pipes to zero.
 * It's used only if I want to clean the memory in the parent process (without exit).
 * @param sh The parameter `sh` is a pointer to a structure of type `t_shell`.
 */
void	reinit_shell(t_shell *sh)
{
	free_token_list(&sh->token_lst);
	ft_bzero(sh->index, sizeof(t_index));
	sh->nbr_pipes = 0;
}

/**
 * The function `init_shell` initializes a shell structure with environment variables and paths.
 * 
 * @param sh The `sh` parameter is a pointer to a `t_shell` structure, which is used to store 
 * information and settings related to the shell program. It is being initialized 
 * in the `init_shell` function.
 * @param env_var The `env_var` parameter in the `init_shell` function is a pointer to an 
 * array of strings that represent environment variables.
 * These environment variables are typically key-value pairs that provide information 
 * about the environment in which the shell is running. 
 * The function initializes the shell structure `t_shell` by setting up
 */
void	init_shell(t_shell *sh, char **env_var)
{
	ft_bzero(sh, sizeof(t_shell));
	sh->index = malloc(sizeof(t_index));
	if (!sh->index)
	{
		write(1, "Malloc error!", 14);
		clear_exit(sh, 1);
	}
	ft_bzero(sh->index, sizeof(t_index));
	if (!env_var[0])
		init_empty_env(sh);
	if (env_var)
	{
		fill_env(sh, env_var);
		sh->envp = list_to_array(sh, sh->env_lst, 2);
		get_paths(sh);
	}
}

int	fork1(t_shell *sh)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("Fork failed\n");
		clear_exit(sh, 1);
	}
	sh->pid = pid;
	return (pid);
}
