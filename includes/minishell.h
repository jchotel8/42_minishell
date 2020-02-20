/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  minishell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:05:57 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/21 16:36:59 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libc.h>
# include "get_next_line.h"
# include "../libs/libft/libft.h"
# include "../libs/ft_printf/includes/printf.h"

#define PROMPT "\x1b[38;2;232;212;98m✦ %s\033[0;0m \x1b[38;2;232;72;119m➜  \x1b[38;2;255;235;202m"

typedef struct	s_shell
{
	char		*read;
	char		**lines;
	char		*cmd;
	char		**arg;
	char		wd[PATH_MAX];
	int			i;
	char		**env;
}				t_shell;

//HANDLE_SH
t_shell	*init_shell();
void 	next_shell(t_shell *sh);
void	debug_shell(t_shell *sh);
void	reset_shell(t_shell *sh);

//PARSING
void	parsing_read(t_shell *sh);
void	parsing_line(t_shell *sh);
void	handle_cmd(t_shell *sh, char **env);

void	handle_pwd(t_shell *sh);
void	handle_cd(t_shell *sh);
void	handle_echo(t_shell *sh);
void	handle_env(t_shell *sh, char **env);
void	handle_bin(t_shell *sh);

#endif
