/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 20:36:01 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/12 05:14:26 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_find_cmd(t_shell *sh, char **paths)
{
	int			i;
	char		*cmd;
	struct stat	buf;

	i = 0;
	if (!stat(sh->cmd[0], &buf))
		return (execve(sh->cmd[0], sh->cmd, ft_lst_to_array(sh->env)));
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(cmd, sh->cmd[0]);
		if (!stat(cmd, &buf))	//stat = trouver le fichier && signal = verifier les droits
			break ;
		i++;
	}
	if (!paths[i])
	{
		ft_printf("\x1b[38;2;255;235;202mCommand not found: %s\n", sh->cmd[0]);
		exit(0);
		return (127);
	}
	else
		return (execve(cmd, sh->cmd, ft_lst_to_array(sh->env)));
}

int	handle_bin(t_shell *sh)
{
	char	**possible_paths;
	t_list	*tmp;
	int		ret;

	tmp = sh->env;
	ret = 1;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "PATH=", 5))
		{
			possible_paths = ft_split(tmp->content + 5, ':');
			ret = ft_find_cmd(sh, possible_paths);
			ft_freearray(possible_paths);
		}
		tmp = tmp->next;
	}
	return (ret);
}
