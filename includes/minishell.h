/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  minishell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:05:57 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/12 03:30:21 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libc.h>
# include "get_next_line.h"
# include "../libs/libft/libft.h"
# include "../libs/ft_printf/includes/printf.h"

#define PROMPT "\x1b[38;2;232;212;98m✦ %s \033[0;0m\x1b[38;2;232;72;119m(%s) ➜  \x1b[38;2;255;235;202m"

typedef struct	s_shell
{
	char		*read;
	char		**lines;   // line 0 : echo bonjour > out1 | cat -e   // line 1 : ls 			;
	char		**pipes;   // pipe 0 : echo bonjour > out1 				// pipe 1 : cat -e		|
	char		**redir;   // redir 0 : echo bonjour					// redir1 : out1 		>
	char		**cmd;	   // cmd 0 : echo cmd1 : bonjour										' '
	char		**arg;	   // cmd++ : cmd1 : bonjour cmd 2 ... cmd3
	char		wd[PATH_MAX];
	int			i_line;
	int			i_pipe;
	int			type;
	int			ret;
	t_list		*env;
}				t_shell;

//extern  int		g_ret;

//UTILITIES
int		switch_inside(char *current, char new, char prev);
int		ft_countquoteignore(char *s);
char	*ft_strtrimignore(char *s);
char	**ft_splitignore(char const *s, char c, int i);
char	*ft_replaceenvignore(t_shell *sh, char *s);
void	ft_list_print_contains(t_list *ptr, int c);
void	ft_list_print_quotes(t_list *ptr);

//ADD TO THE LIBFT
void	ft_list_print(t_list *ptr, int flag);
t_list	*ft_lstcrea(int i, ...);
t_list	*ft_add_array_to_list(t_list *first, char **array);
t_list	*ft_array_to_lst(char **array);
char	**ft_lst_to_array(t_list *lst);
void	ft_print_array(char **array, char *text, int flag);
char 	**ft_array_add_front(char **array, void *data);
int		ft_strncmp_auto(char *s1, char *s2);
void	ft_list_print_if(t_list *ptr, int c);
void	ft_list_print_quote(t_list *ptr);
void	ft_lstadd_sorted(t_list **alst, t_list *new);
void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());
t_list	*ft_list_sort(t_list *lst, int (*cmp)());
int		ft_arraysize(char **array);
void	ft_freearray(char **array);
void	test_utils(void);		//a supprimer

//HANDLE_SH
t_shell	*init_shell(char **env);
void	debug_shell(t_shell *sh);
void	next_shell_pipe(t_shell *sh);
void	next_shell_line(t_shell *sh);
void	clean_shell(t_shell *sh);
void	free_shell(t_shell *sh);

//PARSING
void	parsing_read(t_shell *sh);
void	parsing_line(t_shell *sh);
void	parsing_pipe(t_shell *sh);

//HANDLE
char	*get_wd(t_shell *sh);
void	handle_cmd(t_shell *sh);
int 	handle_pwd(t_shell *sh);
int		handle_cd(t_shell *sh);
int		handle_echo(t_shell *sh);
int 	handle_env(t_shell *sh);
int 	handle_bin(t_shell *sh);
int 	handle_unset(t_shell *sh);
int 	handle_export(t_shell *sh);
void	handle_pipe(t_shell *sh);

#endif
