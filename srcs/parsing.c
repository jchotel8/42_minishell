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

	while (ft_strcountignore(sh->read) % 2)
	{
		ft_printf("dquote>");
		get_next_line(0, &next);
		sh->read = ft_strjoin(sh->read, "\n");
		sh->read = ft_strjoin(sh->read, next);
		free(next);
	}
}

void	parsing_read(t_shell *sh)
{
	prep_read(sh);
	sh->lines = ft_splitignore(sh->read, ';');
	free(sh->read);
}

void	parsing_line(t_shell *sh)
{
	sh->redirs = ft_splitignore(sh->lines[sh->i_line], '>');
	if (sh->redirs[1])
		sh->redirs[1] = *ft_splitignore(sh->redirs[1], ' '); //gerer les cas d'erreurs : s'il y a plus d'un argument
}

void	parsing_redir(t_shell *sh)
{
	sh->tasks = ft_splitignore(sh->redirs[0], '|');
}

void	parsing_task(t_shell *sh)
{
	int	i;

	i = 0;
	sh->cmd = ft_splitignore(sh->tasks[sh->i_task], ' ');
	sh->arg = (sh->cmd[1] ? &sh->cmd[1] : NULL);
	while (sh->arg && sh->arg[i])
	{
		sh->arg[i] = ft_strtrimignore(sh->arg[i]);
		i++;
	}
}
