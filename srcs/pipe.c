/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 18:30:13 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/23 21:01:59 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_pipes(int size, int pipes[size])
{
	int i;

	i = 0;
	while (i < size)
	{
		pipe(pipes + i);
		i += 2;
	}
}

void close_pipes(int size, int *pipes)
{
	while (size--)
	{
		close(pipes[size]);
	}
}

void set_pipe(int j, int size ,int *pipes, char **arg)
{
	if (j > 0)
		dup2(pipes[j - 2], 0);
	if (j <= (size + 2) / 2)
		dup2(pipes[j + 1], 1);
	close_pipes(size, pipes);
	execvp(*arg, arg);
}

void rec_pipe(int j, int size ,int *pipes, char ***args)
{
	j += 2;
	if (fork() == 0)
		set_pipe(j, size,pipes, args[j / 2]);
	else if (j < size)
		rec_pipe(j, size, pipes, args);
}

void ité_pipe(int j, int size ,int *pipes, char ***args)
{
	while (j <= size)
	{
		j += 2;
		if (fork() == 0)
			set_pipe(j, size,pipes, args[j / 2]);
	}
}


void handle_pipe(t_shell *sh, int nb_task)
{
	int status;
	int i = 0;
	static int j = -2;
	int size = nb_task * 2 - 2;
	int pipes[size];

	char **args[nb_task];
	while (sh->tasks && sh->tasks[sh->i_task])
	{
		parsing_task(sh);
		args[sh->i_task] = sh->cmd;
		next_shell_task(sh);
	}
	init_pipes(size, pipes);
	rec_pipe(j, size, pipes, args);
	close_pipes(size, pipes);
	for (i = 0; i < nb_task; i++)
		wait(&status);
}
