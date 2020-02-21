/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 20:36:01 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/21 01:58:05 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void ft_find_cmd(t_shell *sh, char **paths)
{
	int i;
	char *cmd;
	char *argv[] = {sh->cmd , NULL}; //plus tard il faudra sh->arg ici (avec cmd inclu en sh->arg[0] ou tel quel ?)
	char *envp[] = {NULL};			//je crois que oui, man execve, comme dans main (int ac, char **argv - avec argv[0] = a.out
	struct stat buf;
	pid_t child;

	i = 0;
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(cmd, sh->cmd);
		if (!stat(cmd, &buf)) //stat = trouver le fichier && signal = verifer les droits
			break;
		i++;
	}
	if (!paths[i])
		ft_printf("\x1b[38;2;255;235;202mzsh: command not found: %s\n\x1b[38;2;30;30;30m", sh->cmd);
	else
	{
		if (!(child = fork()))
		{
			ft_printf("exec : %d\n", execve(cmd, argv, envp));
			//exit(1); pas sure de l'utilité de ca
		}
		wait(&child);
	}
}

void handle_bin(t_shell *sh, char **env)
{
	int		i;
	char	**possible_paths;

	i = 0;
	while(env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			possible_paths = ft_split(env[i] + 5, ':');
			ft_find_cmd(sh, possible_paths);
		}
		i++;
	}
}
