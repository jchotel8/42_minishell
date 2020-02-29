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

int		main(int ac, char **av, char **env)
{
	t_shell	*sh;

	if (ac > 0)
	{
		av[1] = "bonjour\0";
		//int fd;
		//fd = open(av[1], O_RDWR | O_TRUNC | O_CREAT, 00777);
		sh = init_shell();
		ft_printf(PROMPT, "MINISHELL", get_wd(sh));
		sh->env = ft_array_to_lst(env);
		while (get_next_line(0, &sh->read) > 0)
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
		}
		printf("last read : \"%s\"\n", sh->read);
		free(sh->read);
	}
}
