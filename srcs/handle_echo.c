#include "../includes/minishell.h"

void	handle_echo(t_shell *sh)
{
	int i;
	int flag_n;
	char *tmp;					// = "salut\ncava";

	i = 0;
	flag_n = 0;
	debug_shell(sh);
	if (sh->arg && !ft_strcmp("-n", sh->arg[i]))
	{
		i++;
		flag_n = 1;
	}
	while (sh->arg && sh->arg[i])
	{
		tmp = sh->arg[i];
		sh->arg[i] = ft_strtrim(sh->arg[i], "\"");
		//printf("p sh->arg[i] : %s\n", sh->arg[i]);
		//printf("p str_trim : %s\n", str);
		//printf("p sh->arg[i] : %s\n", "salut\ncava");
		free(tmp);
		ft_printf("\x1b[38;2;255;235;202m%s ", sh->arg[i]);
		i++;
	}
	if (!flag_n)
		ft_printf("\n");		//ce /n ira dans la redirection de fichier,
								//1 autre pour remettre a la ligne dans le terminal
}