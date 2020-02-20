#include "../includes/minishell.h"

void handle_env(t_shell *sh, char **env)
{
	int i;
	sh->i = sh->i;

	i = 0;
	//env[i] = "";
	//ft_printf("%s\n", env[0]);
	while(env[i])
	{
		ft_printf("%s\n", env[i++]);
	}
}