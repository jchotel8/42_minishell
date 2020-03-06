/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:13:05 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/05 19:56:41 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_env(t_shell *sh)
{
	ft_list_print(sh->env, 0);
}

void	handle_unset(t_shell *sh)
{
	ft_list_remove_if(&sh->env, sh->arg[0], *ft_strncmp_auto); //peut être faire un join avec un = sur sh->arg[0] et option majuscule/minuscule ?
} //qu'est ce qui se passe si jai plusieurs arg?

void	handle_export(t_shell *sh)
{
	if (sh->arg && sh->arg[0])
	{
		ft_printf("arg : %s\n", sh->arg[0]);
		ft_lstadd_back(&sh->env, ft_lstnew(sh->arg[0])); //questce qui se passe si sh->arg n'est pas au format MAVARIABLE="blabla"?
	}
	else
	{
		ft_list_sort(sh->env, ft_strcmp);
		ft_list_print(sh->env, 0);
	}
}
