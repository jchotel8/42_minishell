/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:31:27 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/23 20:03:09 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prep_read(t_shell *sh)
{
	char	*next;
	char	*tmp;

	while (ft_strcountignore(sh->read) % 2)
	{
		ft_printf("dquote>");
		get_next_line(0, &next);
		tmp = sh->read;
		sh->read = ft_strjoin(sh->read, "\n");
		free(tmp);
		tmp = sh->read;
		sh->read = ft_strjoin(sh->read, next);
		free(tmp);
		free(next);
	}
}

void	parsing_read(t_shell *sh)
{
	prep_read(sh);
	sh->lines = ft_splitignore(sh->read, ';', 1);
	free(sh->read);
	sh->read = 0;
}

void	parsing_line(t_shell *sh)
{
	sh->pipes = ft_splitignore(sh->lines[sh->i_line], '|', 1);
}

void	parsing_pipe(t_shell *sh)
{
	int	i;

	i = 0;
	sh->redir = ft_splitignore(sh->pipes[sh->i_pipe], '>', 0);
	sh->cmd = ft_splitignore(sh->redir[0], ' ', 1);
	sh->arg = (sh->cmd[1] ? &sh->cmd[1] : NULL);
	while (sh->arg && sh->arg[i])
	{
	 	sh->arg[i] = ft_strtrimignore(sh->arg[i]); //wesh pourquoi on utilise se ft_strtrim trop moche!?
	 	i++;
	}
	if (sh->redir[1]) //si > attention il faut aussi verifier dans le cas ou > est placé au début donc !sh->redir[1]
	{
	 	if (ft_strcmp(">", sh->redir[1]) == 0)
	 	{
	 		sh->type = 1;
	 		sh->redir[1] = sh->redir[2];
	 	}
	 	sh->redir[1] = ft_strtrim(sh->redir[1], "> ");
	}
}
