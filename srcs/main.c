/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:12:08 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_cmd(t_shell *sh)
{
	//if (!ft_strcmp(sh->cmd[0], "echo"))
	//	return (handle_echo(sh));
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
	int nb_pipe = 0;

	if (sh->pipes)
	{
		if ((nb_pipe = ft_arraysize(sh->pipes)) > 0)
		{//si > 0, sauf le exit et le mélange bin : a cause des forks... il ne faut pas fork si exit?
			handle_pipe(sh);
		}
		else
		{//je veux absoluement supprimer ce else pour que handle_pipe gere tout correctement
			parsing_pipe(sh);
			handle_cmd(sh);
		}
	}
}

void sigint_handler(int sig)
{
	int		status;

	(void)sig;
	waitpid(-1, &status, 0);
	if (WTERMSIG(status) == SIGINT)
	{
		ft_printf("\n");
		g_sh->ctrlc = 1;
	}
	else
	{
		ft_printf("\b\b  \n");
		ft_printf(PROMPT, "MINISHELL", get_wd(g_sh));
		g_sh->ctrlc = 1;
	}
}

void sigquit_handler(int sig)
{
	int		status;

	(void)sig;
	waitpid(-1, &status, 0);
	if (WTERMSIG(status) == SIGQUIT)
		ft_printf("Quit: 3\n");
	else
		ft_printf("\b\b  \b\b");
}

void main_loop2(t_shell *sh)
{
	int ret = get_next_line(0, &sh->read);
	if (ret > 0)
		main_loop(sh, 1);
	else
		main_loop2(sh);
}

void main_loop(t_shell *sh, int ret2)
{

	int ret = ret2;
	 if (ret2 == 0)
	 	ret = get_next_line(0, &sh->read);
	if (ret > 0)
	{
		parsing_read(sh);
		clean_shell(sh);
		while (sh->lines[sh->i_line])
		{
			parsing_line(sh);
			handle_line(sh);
			next_shell_line(sh);
		}
		ft_printf(PROMPT, "MINISHELL", get_wd(sh));
		main_loop(sh, 0);
	}
	else if (sh->read[0])
	{
		main_loop2(sh);
	}
}

int		main(int ac, char **av, char **env)
{
	t_shell	*sh;

	if (ac > 0)
	{
		av[1] = "bonjour\0";
		//int fd;
		//fd = open(av[1], O_RDWR | O_TRUNC | O_CREAT, 00777);
		sh = init_shell();
		sh->env = ft_array_to_lst(env);
		sh->ctrlc = 0;
		g_sh = sh;
		ft_printf(PROMPT, "MINISHELL", get_wd(sh));
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigquit_handler);
		main_loop(sh, 0);
		ft_printf("exit");
		if(!sh->ctrlc)
			ft_printf("\n");
		free(sh->read);
	}
}
