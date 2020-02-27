/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 18:30:13 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/24 16:22:37 by jchotel          ###   ########.fr       */
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
	if (j > 0)
		dup2(pipes[j - 2], 0);
	if (j <= (nb_pipes + 2) / 2)
		dup2(pipes[j + 1], 1);
	close_pipes(nb_pipes, pipes);
	handle_cmd(sh);
	//execvp(*sh->tab_arg[j / 2], sh->tab_arg[j / 2]);
}

void	set_pipe_rec(int j, int nb_pipes, int *pipes, t_shell *sh)
{
	j += 2;
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

void	handle_pipe(t_shell *sh, int nb_task)
{
	int			status;
	int			i;
	static int	j = -2;
	int			nb_pipes = nb_task * 2 - 2;
	int			pipes[nb_pipes];
	char		**args[nb_task];

	while (sh->tasks && sh->tasks[sh->i_task])
	{
		parsing_task(sh);
		debug_shell(sh);
		args[sh->i_task] = sh->cmd;
		next_shell_task(sh);
	}
	sh->tab_arg = args;
	init_pipes(nb_pipes, pipes);
	set_pipe_rec(j, nb_pipes, pipes, sh);
	close_pipes(nb_pipes, pipes);
	i = 0;
	while (i < nb_task)
	{
		wait(&status);
		i++;
	}
}
