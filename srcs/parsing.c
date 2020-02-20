#include "../includes/minishell.h"

void parsing_read(t_shell *sh)
{
	sh->lines = ft_split(sh->read, ';');
	sh->read = 0;
	free(sh->read);
}

void prep_arg(t_shell *sh)
{
	int i = 0;

	while (sh->arg && sh->arg[i])
	{
		if (ft_strchr(sh->arg[i], '"'))
			ft_printf("sh->arg[%d] contains \"\n", i);
		else
			ft_printf("sh->arg[%d] empty\n", i);
		i++;
	}
}

void parsing_line(t_shell *sh)
{
	int i;
	int len;

	i = 0;
	len = 0;
	sh->arg = ft_split(sh->lines[sh->i], ' ');
	sh->cmd = sh->arg[0];
	sh->arg = (sh->arg[1] ? &sh->arg[1] : NULL);
	prep_arg(sh);
}
