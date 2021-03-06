/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:12:08 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/12 05:28:59 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler(int sig)
{
	(void)sig;
	ft_putchar('\n');
	ft_printf(PROMPT, "MINISHELL", "stopped");
//	if (CHILD)
//	{
//		kill(CHILD, SIGINT);
//		CHILD = 0;
//	}
}

void		handle_cmd(t_shell *sh)
{
	pid_t pid;

	if (!ft_strcmp(sh->cmd[0], "echo"))
		sh->ret = handle_echo(sh);
	else if (!ft_strcmp(sh->cmd[0], "cd"))
		sh->ret = handle_cd(sh);
	else if (!ft_strcmp(sh->cmd[0], "pwd"))
		sh->ret = handle_pwd(sh);
	else if (!ft_strcmp(sh->cmd[0], "exit"))
		exit(0);
	else if (!ft_strcmp(sh->cmd[0], "unset"))
		sh->ret = handle_unset(sh);
	else if (!ft_strcmp(sh->cmd[0], "env"))
		sh->ret = handle_env(sh);
	else if (!ft_strcmp(sh->cmd[0], "export"))
		sh->ret = handle_export(sh);
	else if (ft_arraysize(sh->pipes) == 1)
	{
		if ((pid = fork()) == 0)
			sh->ret = handle_bin(sh);
		waitpid(pid, &sh->ret, 0);
	}
	else
	{
		sh->ret = handle_bin(sh);
		return ;
	}
}

void	handle_line(t_shell *sh)
{
	int	out;
	int	i;
	pid_t pid = 0;

	i = 0;
	if (sh->pipes)
	{
		if (ft_arraysize(sh->pipes) > 1)
			handle_pipe(sh);
		else
		{
			parsing_pipe(sh);
			if (ft_arraysize(sh->redir) > 1 && (pid = fork()) == 0)
			{
				while (sh->redir[i])
				{
					if (sh->type == 0)
						out = open(sh->redir[i], 1537, 0644);
					else
						out = open(sh->redir[i], 521, 0644);
					dup2(out, 1);
					close(out);
					i++;
				}
				handle_cmd(sh);
				exit(0);
			}
			waitpid(pid, &sh->ret, 0);
			if (ft_arraysize(sh->redir) == 1)
				handle_cmd(sh);
		}
	}
}

int		main(int ac, char **av, char **env)
{
	t_shell	*sh;

	if (ac > 0)
	{
		(void)av;
		(void)env;
		sh = init_shell(env);
		signal(SIGINT, sig_handler);
		ft_printf(PROMPT, "MINISHELL", get_wd(sh));
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
		printf("quitting minishell : \"%s\"\n", sh->read);
		free(sh->read);
	}
}
