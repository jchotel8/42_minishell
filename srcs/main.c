/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:12:08 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/21 07:48:35 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	option_cmd(t_shell *sh)
{
	if (!ft_strcmp(sh->cmd, "echo"))
		return (handle_echo(sh));
	if (!ft_strcmp(sh->cmd, "cd"))
		return (handle_cd(sh));
	if (!ft_strcmp(sh->cmd, "pwd"))
		return (handle_pwd(sh));
	if (!ft_strcmp(sh->cmd, "exit"))
		return (exit(0));
	if (!ft_strcmp(sh->cmd, "unset"))
		return (handle_unset(sh));
	if (!ft_strcmp(sh->cmd, "env"))
		return (handle_env(sh));
	if (!ft_strcmp(sh->cmd, "export"))
		return handle_export(sh);
	else
		return (handle_bin(sh));
}

void	handle_line(t_shell *sh)
{
	int			pipefd[2];
	while (sh->tasks[sh->i_task])
	{
		parsing_task(sh);
		if (sh->i_task)
			sh->arg = ft_array_add_front(sh->arg, "pipe.txt");
		debug_shell(sh);
		if (sh->tasks[sh->i_task + 1])
		{
			pipe(pipefd);
			pipefd[0] = open("pipe.txt", O_RDWR | O_TRUNC, 00777);
			if (!fork())
			{
				dup2(pipefd[0], 1);
				option_cmd(sh);
				close(pipefd[0]);
				exit(1);
			}
			ft_printf("piping du resultat en cours...\n");
			sh->pipefd = pipefd[0];
		}
		else
			option_cmd(sh);
		next_shell_cmd(sh);
	}
}

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
			next_shell_line(sh);
			while (sh->lines[sh->i_line])
			{
				parsing_line(sh);
				handle_line(sh);
				next_shell_task(sh);
			}
			ft_printf(PROMPT, "MINISHELL", get_wd(sh));
		}
		printf("last read : \"%s\"\n", sh->read);
		free(sh->read);
	}
}
