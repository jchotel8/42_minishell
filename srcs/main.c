/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:12:08 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/23 20:30:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_cmd(t_shell *sh)
{
	if (!ft_strcmp(sh->cmd[0], "echo"))
		return (handle_echo(sh));
	if (!ft_strcmp(sh->cmd[0], "cd"))
		return (handle_cd(sh));
	if (!ft_strcmp(sh->cmd[0], "pwd"))
		return (handle_pwd(sh));
	if (!ft_strcmp(sh->cmd[0], "exit"))
		return (exit(0));
	if (!ft_strcmp(sh->cmd[0], "unset"))
		return (handle_unset(sh));
	if (!ft_strcmp(sh->cmd[0], "env"))
		return (handle_env(sh));
	if (!ft_strcmp(sh->cmd[0], "export"))
		return handle_export(sh);
	else
		return (handle_bin(sh));
}

void	handle_line(t_shell *sh)
{
	int nb_task;

	//while (sh->tasks && sh->tasks[sh->i_task])
	if (sh->tasks)
	{
		if ((nb_task = ft_tabsize(sh->tasks)) > 1)
		{//DANS LE CAS DE PIPE
			handle_pipe(sh, nb_task);
		}
		else
		{
			parsing_task(sh);
			debug_shell(sh);
			handle_cmd(sh);
		}
		wait(NULL);
		//next_shell_task(sh);
	}
}

//void handle_line(t_shell *sh)
//{
//	parsing_task(sh);
//	debug_shell(sh);
	//int status;
	//int i;

//	static int j = -2;
//	int nb = 4;
//	int size = nb * 2 - 2;
//	char *cat_args[] = {"cat", "/dev/random", NULL};
//	char *grep_args[] = {"head", "-n", "10", NULL};
//	char *grep_args2[] = {"head", "-n", "5", NULL};
//	char *cut_args[] = {"cut", "-b", "1-10", NULL};
//
//	char ***args = NULL;
//	args[0] = cat_args;
//	args[1] = grep_args;
//	args[2] = grep_args2;
//	args[3] = cut_args;
//
//	int pipes[size];
//	pipe(pipes); // sets up 1st pipe
//	pipe(pipes + 2); // sets up 2nd pipe
//	pipe(pipes + 4);
//
//
//	rec_pipe(j, size, pipes, args);
//	close_pipes(size, pipes);
//	for (i = 0; i < 4; i++)
//		wait(&status);
//	ft_printf("hello\n");
//}

int		main(int ac, char **av, char **env)
{
//	test_utils();
	t_shell	*sh;
	if (ac > 0)
	{
		av[1] = 0;
		sh = init_shell();
		ft_printf(PROMPT, "MINISHELL", get_wd(sh));
		sh->env = ft_array_to_lst(env);
		while (get_next_line(0, &sh->read) > 0)
		{
			parsing_read(sh);
			start_shell_line(sh);
			while (sh->lines[sh->i_line])
			{
				parsing_line(sh);
				handle_line(sh);
				next_shell_line(sh);
			}
			ft_printf(PROMPT, "MINISHELL", get_wd(sh));
		}
		printf("last read : \"%s\"\n", sh->read);
		free(sh->read);
	}
}
