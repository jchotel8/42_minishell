/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:31:27 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/21 02:35:45 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prep_arg(t_shell *sh)
{
	char	*next;

	while (ft_strcount(sh->read, '"') % 2)
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
	prep_arg(sh);
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
	int	len;

	i = 0;
	len = 0;
	sh->arg = ft_splitignore(sh->tasks[sh->i_task], ' ');
	sh->cmd = sh->arg[0];
	sh->arg = (sh->arg[1] ? &sh->arg[1] : NULL);
}
