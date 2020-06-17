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
	int	pipefd[2];
	pid_t son;
	if (sh->tasks[sh->i_task])
	{
		parsing_task(sh);
		debug_shell(sh);
		if (sh->tasks[sh->i_task + 1])
		{
			pipe(pipefd);
			if (!(son = fork()))
			{
				dup2(pipefd[1], 1);
				handle_cmd(sh);
				//close(pipefd[0]);
				//close(pipefd[1]); utile ?
				exit(1);
			}
			dup2(pipefd[0], 0);
			close(pipefd[1]);
			ft_printf("piping du resultat en cours...\n");
			next_shell_task(sh);
			handle_line(sh);
			//kill(-wait(0),SIGKILL);
			close(pipefd[0]);
			//kill(son,0);
			//kill(son,-1);
			//kill(son2,SIGKILL);
			//kill(son,-2);
		}
		else
			handle_cmd(sh);
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
				if (!fork())
				{
					handle_line(sh);
					exit(1);
				}
				wait(0);
				sh->i_task = 0;
				next_shell_line(sh);
			}
			ft_printf(PROMPT, "MINISHELL", get_wd(sh));
		}
		printf("last read : \"%s\"\n", sh->read);
		free(sh->read);
	}
}
