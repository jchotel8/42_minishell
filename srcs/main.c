/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:12:08 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/24 16:15:29 by jchotel          ###   ########.fr       */
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
		return (handle_export(sh));
	else
		return (handle_bin(sh));
}

void	handle_line(t_shell *sh)
{
	int nb_task = 0;

	if (sh->tasks)
	{
		if ((nb_task = ft_tabsize(sh->tasks)) > 1)
		{//est-ce que handle_pipe gère le cas de nb_task = 1 ?
			handle_pipe(sh, nb_task);	//il faut utiliser handle_cmd(sh) à la place de simplement execve
		}
		else
		{
			if (!fork())
			{
				/*if(sh->fd_redir)
					dup2(sh->fd_redir, 0);*/
				parsing_task(sh);
				debug_shell(sh);
				if(sh->fd_redir)
					dup2(sh->fd_redir, 1);
				handle_cmd(sh);
				exit(0);
			}
			wait(0);
		}
	}
}

int		check_exit(t_shell *sh)
{
	while (sh->tasks[sh->i_task])
	{
		parsing_task(sh);
		if (!ft_strcmp(sh->cmd[0], "exit"))
			return (1);
		next_shell_task(sh);
	}
	sh->i_task = 0;
	return(0);
}


int		main(int ac, char **av, char **env)
{
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
				if (check_exit(sh))
					return (0);
				handle_line(sh);
				next_shell_line(sh);
			}
			ft_printf(PROMPT, "MINISHELL", get_wd(sh));
		}
		printf("last read : \"%s\"\n", sh->read);
		free(sh->read);
	}
}
