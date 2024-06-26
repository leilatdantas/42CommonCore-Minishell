/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:16:52 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/26 19:16:39 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signo;

void	run_tree(t_shell *sh)
{
	set_child_signals();
	parsing_tree(sh);
	exec_tree(sh, sh->cmd);
}

/**
 * The function `run_loop` continuously prompts for input, validates syntax, processes commands, 
 * and handles signals in a shell program.
 * 
 * @param sh The `sh` parameter is a pointer to a structure of type `t_shell`, 
 * which likely contains information and settings related to the shell environment. 
 * It is used within the `run_loop` function to interact with the shell, handle input, 
 * execute commands, and manage the shell state.
 * @param prompt_input The `prompt_input` parameter in the `run_loop` function is a 
 * character pointer that stores the input provided by the user in the shell prompt. 
 * It is used to read user commands and execute them within the shell loop.
 * @param status The `status` parameter in the `run_loop` function is used to store the exit status 
 * of the child process that is executed using `fork1` and waited for using `waitpid`. 
 * This status is then checked using `WIFEXITED` and `WEXITSTATUS` to determine if the child process 
 * exited normally and to retrieve the exit
 */
void	run_loop(t_shell *sh, char *prompt_input, int status)
{
	while (1)
	{
		prompt_input = get_line(sh);
		if (!prompt_input)
			sh_loop(sh);
		if (!sintax_validation(prompt_input))
		{
			add_history(prompt_input);
			free(prompt_input);
			sh_loop(sh);
		}
		set_main_signal();
		lexer(sh, prompt_input);
		add_history(prompt_input);
		free(prompt_input);
		if (fork1(sh) == 0)
			run_tree(sh);
		waitpid(0, &status, 0);
		if (WIFEXITED(status))
			g_signo = WEXITSTATUS(status);
		set_signals();
		if (sh->nbr_pipes == 0)
			builtins_parent(sh);
		reinit_shell(sh);
	}
}

void	sh_loop(t_shell *sh)
{
	char	*prompt_input;
	int		status;

	prompt_input = NULL;
	status = 0;
	set_signals();
	run_loop(sh, prompt_input, status);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	input_check(argc, argv);
	init_shell(&sh, envp);
	sh_loop(&sh);
	clear_exit(&sh, 0);
	return (0);
}

// ctrl-D on empty prompt

//     quit minishell
//     echo $? must display 0

// ctrl-C in cat without arguments

//     ^C
//     echo $? must display 130

// ctrl-\ in cat without arguments

//     \Quit (core dumped)
//     echo $? must display 131
