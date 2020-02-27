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
	sh->tasks = ft_splitignore(sh->lines[sh->i_line], '|');
}

void	parsing_task(t_shell *sh)
{
	int	i;
	int	found_chev = 0;

	i = 0;
	sh->fd_redir = 0;
	sh->cmd = ft_splitignore(sh->tasks[sh->i_task], ' ');
	while (sh->cmd[i])
	{
		sh->cmd[i] = ft_strtrimignore(sh->cmd[i]);
		i++;
	}
	i = 0;
	while (sh->cmd[i])
	{
		if (sh->cmd[i][0] == '>')
		{
			found_chev = 1 + (sh->cmd[i][1] == '\0');
			sh->fd_redir = open(sh->cmd[i + found_chev - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
		}
		sh->cmd[i] = sh->cmd[i + found_chev];
		i++;
	}
	sh->arg = (sh->cmd[1] ? &sh->cmd[1] : NULL);
}
