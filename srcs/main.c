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

void	handle_cmd(t_shell *sh)
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
	char	nomfichier[2];
	nomfichier[1] = '\0';
	nomfichier[0] = '0';
	while (sh->tasks[sh->i_task])
	{
		parsing_task(sh);
		if (sh->i_task)
			sh->arg = ft_array_add_front(sh->arg, nomfichier);
		debug_shell(sh);
		nomfichier[0] = '0' + sh->i_task;
		if (sh->tasks[sh->i_task + 1])
		{
			sh->pipefd = open(nomfichier, O_RDWR | O_TRUNC | O_CREAT, 00777);
			if (!(fork()))
			{
				dup2(sh->pipefd, 1);
				handle_cmd(sh);
				exit(1);
			}
			ft_printf("piping du resultat en cours...\n");
		}
		else
			handle_cmd(sh);
		wait(NULL);
		next_shell_task(sh);
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
