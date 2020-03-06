/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:13:05 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/06 17:19:24 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_env(t_shell *sh)
{
	ft_list_print(sh->env, 0);
}

void	handle_unset(t_shell *sh)
{
	int		i;
	char	*tmp;

	i = 0;
	while (sh->arg[i])
	{
		tmp = sh->arg[i];
		sh->arg[i] = ft_strjoin(sh->arg[i], "=");
		free(tmp);
		ft_list_remove_if(&sh->env, sh->arg[i], *ft_strncmp_auto);
		i++;
	}
}

void	handle_export(t_shell *sh)
{
	if (sh->arg && sh->arg[0])
	{
		ft_printf("arg : %s\n", sh->arg[0]);
		ft_lstadd_back(&sh->env, ft_lstnew(sh->arg[0]));
	}
	else
	{
		ft_list_sort(sh->env, ft_strcmp);
		ft_list_print(sh->env, 0);
	}
}
