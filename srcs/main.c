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
	(void)sig;
	 //printf("killing process %d\n",getpid());
	 //exit(0);
	 write(0, "\n", 1);
	 kill(-fils, 0);
	 //main(1, NULL, g_env);
	 //main_loop(g_env);
	 //exit(0);
}
/*
void main_loop(char **env)
{

}*/

int		main(int ac, char **av, char **env)
{
	g_env = env;
	if (ac > 0)
	{
		av[1] = "bonjour\0";
		//int fd;
		//fd = open(av[1], O_RDWR | O_TRUNC | O_CREAT, 00777);
		t_shell	*sh;
		//signal(SIGINT, sigint_handler);
		sh = init_shell();
		sh->env = ft_array_to_lst(env);
		//signal(SIGINT, sigint_handler);
		ft_printf(PROMPT, "MINISHELL", get_wd(sh));
		//signal(SIGINT, sigint_handler);
		while (get_next_line(0, &sh->read) > 0)
		{
			//if(!(fils = fork()))
			//{
			parsing_read(sh);
			clean_shell(sh);
			while (sh->lines[sh->i_line])
			{
				parsing_line(sh);
				//debug_shell(sh);
				handle_line(sh);
				next_shell_line(sh);
			//}
			ft_printf(PROMPT, "MINISHELL", get_wd(sh));
			}
			//else
			//{

			//	wait(0);
			//}
		}
		printf("last read : \"%s\"\n", sh->read);
		free(sh->read);
	}
}
