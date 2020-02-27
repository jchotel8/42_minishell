/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  minishell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:05:57 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/23 20:17:12 by jchotel          ###   ########.fr       */
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
	int			fd_redir;
	char		**lines;
	char		**tasks;
	char		**cmd;
	char		**arg;
	char		***tab_arg;
	char		wd[PATH_MAX];
	int			i_line;
	int			i_task;
	t_list		*env;

}				t_shell;

//UTILITIES
int		switch_inside(char *current, char new, int *inside);
int		ft_strcountignore(char *s);
char	*ft_strtrimignore(char *s);
char	**ft_splitignore(char const *s, char c);
void	ft_list_print(t_list *ptr, int flag);
t_list	*ft_lstcrea(int i, ...);
t_list	*ft_array_to_lst(char **array);
char	**ft_lst_to_array(t_list *lst);
void	ft_print_array(char **array, char *text, int flag);
char 	**ft_array_add_front(char **array, void *data);
void	test_utils(void);
int		ft_strncmp_auto(char *s1, char *s2);
void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());
int		ft_tabsize(char **tab);

//HANDLE_SH
t_shell	*init_shell();
void	debug_shell(t_shell *sh);
void	next_shell_task(t_shell *sh);
void	next_shell_line(t_shell *sh);
void	start_shell_line(t_shell *sh); //->utilités ?

//PARSING
void	parsing_read(t_shell *sh);
void	parsing_task(t_shell *sh);
void	parsing_line(t_shell *sh);

//HANDLE
char	*get_wd(t_shell *sh);
void	handle_cmd(t_shell *sh);
void	handle_pwd(t_shell *sh);
void	handle_cd(t_shell *sh);
void	handle_echo(t_shell *sh);
void	handle_env(t_shell *sh);
void	handle_bin(t_shell *sh);
void	handle_unset(t_shell *sh);
void	handle_export(t_shell *sh);

//PIPE
void	handle_pipe(t_shell *sh, int nb_task);

#endif
