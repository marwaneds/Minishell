/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:37:09 by cortiz            #+#    #+#             */
/*   Updated: 2023/07/17 09:35:47 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# define HEREDOC_MSG	"> "
# define READLINE_MSG	"minishell> "

typedef struct s_global
{
	int	error_num;
	int	stop_heredoc;
	int	in_cmd;
	int	in_heredoc;
}	t_global;

t_global	g_global;

typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_tokens;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_parser_data
{
	t_lexer			*lexer_list;
	t_lexer			*redirections;
	int				num_redirections;
	struct s_data	*data;
}	t_parser_data;

typedef struct s_data
{
	char					*args;
	char					**paths;
	char					**envp;
	struct s_cmds			*cmds;
	t_lexer					*lexer_list;
	char					*pwd;
	char					*old_pwd;
	int						pipes;
	int						*pid;
	bool					heredoc;
	bool					reset;
}	t_data;

typedef struct s_cmds
{
	char					**str;
	char					*builtin;
	int						num_redirections;
	char					*hd_file_name;
	t_lexer					*redirections;
	struct s_cmds			*next;
	struct s_cmds			*prev;
}	t_cmds;

int				parse_envp(t_data *data);
int				find_pwd(t_data *data);
int				parser(t_data *data);
t_parser_data	init_parser_data(t_lexer *lexer_list, t_data *data);
void			count_pipes(t_lexer *lexer_list, t_data *data);
int				count_args(t_lexer *lexer_list);
int				add_new_redirection(t_lexer *tmp, t_parser_data *parser_data);
void			rm_redirections(t_parser_data *parser_data);
int				parse_envp(t_data *data);
int				find_pwd(t_data *data);
int				reset_data(t_data *data);
char			**expander(t_data *data, char **str);
char			*expander_str(t_data *data, char *str);
size_t			dollar_sign(char *str);
char			*char_to_str(char c);
int				after_dol_lenght(char *str, int j);
void			init_signals(int process);
int				question_mark(char **tmp);
int				count_quotes(char *line);
int				implement_data(t_data *data);
char			**ft_arrdup(char **arr);
void			free_arr(char **split_arr);
int				loop(t_data *data);
int				loop_through_str(char *str);
int				is_quotes(char c);
bool			is_between_single(char *str, char c);
t_cmds			*ft_cmdsnew(char **str, int num_redir, t_lexer *redir);
void			ft_cmdsadd_back(t_cmds **lst, t_cmds *new);
void			ft_cmdsclear(t_cmds **lst);
t_cmds			*ft_cmdsfirst(t_cmds *map);
t_lexer			*ft_lexernew(char *str, int token);
void			ft_lexeradd_back(t_lexer **lst, t_lexer *new);
void			ft_lexerdelone(t_lexer **lst, int i);
void			ft_lexerclear(t_lexer **lst);
void			skip_quotes(int *i, char *str, char quote);
int				is_token(char c);
int				token_reader(t_data *data);
void			change_path(t_data *data);
int				check_builtins(t_data *data, t_cmds *cmd,
					char *str);
int				builtin_echo(t_data *data, t_cmds *cmd);
int				builtin_cd(t_data *data, t_cmds *cmd);
int				builtin_pwd(t_data *data, t_cmds *cmd);
int				builtin_export(t_data *data, t_cmds *cmd);
int				builtin_unset(t_data *data, t_cmds *cmd);
int				builtin_env(t_data *data, t_cmds *cmd);
int				builtin_exit(t_data *data, t_cmds *cmd);
size_t			equal_sign(char *str);
int				check_valid_identifier(char c);
void			parser_error(int error, t_data *data, t_lexer *lexer_list);
int				parser_double_token_error(t_data *data, t_lexer *lexer_list,
					t_tokens token);
int				cmd_not_found(char *str);
int				export_error(char *c);
int				ft_error(int error, t_data *data);
int				check_redirections(t_cmds *cmd);
int				executor(t_data *data);
t_cmds			*call_expander(t_data *data, t_cmds *cmd);
int				pipe_wait(int *pid, int amount);
int				find_cmd(t_cmds *cmd, t_data *data);
void			handle_cmd(t_cmds *cmd, t_data *data);
void			dup_cmd(t_cmds *cmd, t_data *data, int end[2], int fd_in);
void			single_cmd(t_cmds *cmd, t_data *data);
int				send_heredoc(t_data *data, t_cmds *cmd);
int				export_env_declare(t_data *data);

#endif