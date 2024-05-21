/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:57:58 by uviana-a          #+#    #+#             */
/*   Updated: 2024/05/21 18:31:48 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libraries/libft/libft.h"

//COLORS
# define ROSE "\x1b[38;207;1m"
# define ROSE_2 "\x1b[38;5;177;1m"
# define LIGHTGREEN "\x1b[38;5;155;1m"
# define LIGHTBLUE "\x1b[38;5;39;1m"
# define LIGHTPURPLE "\x1b[38;5;63;1m"
# define PURPLE "\x1b[38;5;135;1m"
# define PINK "\x1b[38;5;199;1m"
# define RED "\x1b[38;5;160;1m"
# define ORANGE "\x1b[38;5;172;1m"
# define YELLOW "\x1b[38;5;184;1m"
# define BLUE_BG "\033[38;5;159;48;5;16;1m"
# define COLOR_RESET "\033[0m"

// STRUCTURES
typedef struct s_env
{
	char			*key;
	char			*value;
	bool			visible;
}	t_env;

typedef enum s_token_type
{
	WORD,
	PIPE,
	GREATER,
	LESSER,
	D_GREATER,
	D_LESSER,
	E_SPACE,
	APPEND,
	OUTFILE,
	INFILE,
	HEREDOC
}	t_token_type;

typedef enum s_token_state
{
	GENERAL,
	IN_DQUOTES,
	IN_SQUOTES
}	t_token_state;

typedef struct s_index
{
	int	start;
	int	end;
	int	pos;
}	t_index;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_token_state	state;
	int				pos;
	bool			not_expand;
}	t_token;

typedef struct s_shell
{
	t_list		*env_lst;
	t_list		*token_lst;
	t_index		*index;
}	t_shell;

// MACROS
# define PROMPT "MINISHELL ➜ "
# define OPERATOR "|<>"
# define OUTOFSCOPE "()*;&"
# define OPERATORS_EX "@$?*#-!"

// EXITING THE GLOBAL VARIABLE
extern int	g_signo;

// FUNCTION PROTOTYPES
// ENVIRONMENT FOLDER
// env.c
void	fill_env(t_shell *sh, char **env_var);

// EXIT FOLDER
//exit.c
void	free_env_list(t_list **env_lst);
void	free_token_list(t_list **token_list);
void	clear_exit(t_shell *sh, int status);
void	free_token_list(t_list **token_list);
void	free_token_content(void *content);

// INPUT FOLDER
// input_checker.c
void	input_check(int argc, char **argv, char **envp);
bool	sintax_validation(char *input);

// input_checker_utils.c
bool	only_white(char *input, int curr_pos);
bool	is_a_pipe(char c);
bool	is_a_bigger(char c);
bool	is_a_smaller(char c);

// sintax_valid.c
bool	check_bigger(char *input, int i);
bool	check_smaller(char *input, int i);
bool	spc_char_check(char *input, int i);
bool	prt_stx_error(char *error, bool exit);

// HANDLING SIGNAL
// signals.c
void	reset_signal(void);

//TOKENIZATION
//tokens.c
void	fill_token_lst(t_shell *sh, char *input);

//tokens_aux.c
void	search_word(char *input, int *end);
void	search_quote(char *input, int *j, char c);
int		search_char(char *str, char c);

//rename_tkn_typ.c
bool	chk_typ(int type, int inf, int sup);
void	repl_tkn_typ(t_token *tkn_src, t_token *tkn_des);
void	review_tkn_typ(t_list *tkn_lst);

//expander.c
void	expand_quotes(t_shell *sh, t_list *token);
void	expand_general(t_shell *sh, t_list *tkn);
char	*expansion(t_list *env_list, char *str, int *i);
char	*get_env(t_list *env_list, char *token);

//expander_aux.c
t_token	*get(t_list *token);
void	remove_node(t_list **list, t_list *node);
char	*simple_expand(char token);
int		check_exp(char key);
char	*get_word(char *str, int *i);

//lexer.c
void	lexer(t_shell *sh, char *input);

//lexer_aux.c
int		is_removable(int type);

//EXTRA AUXILIARS
//print.c
void	print_env(t_shell *sh);
void	print_tokens(t_shell *sh);

#endif
