/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 18:30:13 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/06 14:33:53 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_pipes(int nb_pipes, int *pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		pipe(pipes + i);
		i += 2;
	}
}

void	close_pipes(int nb_pipes, int *pipes)
{
	while (nb_pipes--)
	{
		close(pipes[nb_pipes]);
	}
}

void	set_pipe(int j, int nb_pipes, int *pipes, t_shell *sh)
{
	int i;

	i = 0;
	if (j > 0)
		dup2(pipes[j - 2], 0);
	if (j <= (nb_pipes + 2) / 2)
		dup2(pipes[j + 1], 1);
	sh->i_pipe = j / 2;
	parsing_pipe(sh);
	while (sh->redir[i])
	{
     	if (sh->type == 0)
			pipes[j + 1] = open(sh->redir[i], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
     	else
			pipes[j + 1] = open(sh->redir[i], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
     	dup2(pipes[j + 1], 1);
     	i++;
   	}
	close_pipes(nb_pipes, pipes);
	handle_cmd(sh);
	exit(0);
}

void	set_pipe_rec(int j, int nb_pipes, int *pipes, t_shell *sh)
{
	j += 2;
	sh->i_pipe = j;
	if (fork() == 0)
		set_pipe(j, nb_pipes, pipes, sh);
	else if (j < nb_pipes)
		set_pipe_rec(j, nb_pipes, pipes, sh);
}

void	set_pipe_iter(int j, int nb_pipes, int *pipes, t_shell *sh)
{
	while (j <= nb_pipes)
	{
		j += 2;
		if (fork() == 0)
			set_pipe(j, nb_pipes, pipes, sh);
	}
}

void	handle_pipe(t_shell *sh)
{
	int			status;
	int			i;
	static int	j = -2;
	int			nb_pipes = ft_arraysize(sh->pipes) * 2 - 2;
	int			pipes[nb_pipes];

	init_pipes(nb_pipes, pipes);
	set_pipe_rec(j, nb_pipes, pipes, sh);
	close_pipes(nb_pipes, pipes);
	i = 0;
	while (i < ft_arraysize(sh->pipes))
	{
		wait(&status);
		i++;
	}
}
