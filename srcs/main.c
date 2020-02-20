#include "../includes/minishell.h"



int	main(int ac, char **av, char **env)
{
	t_shell	*sh;

	if (ac > 0)
	{
		av[1] = 0;
		sh = init_shell();
		ft_printf(PROMPT, "MY MINISHELL");
		sh->env = env;
		while (get_next_line(0, &sh->read) > 0)
		{
			next_shell(sh);
			parsing_read(sh);
			while (sh->lines[sh->i])
			{
				parsing_line(sh);
				handle_cmd(sh, env);
				sh->i++;
			}
			ft_printf(PROMPT, "MY MINISHELL");
		}
		printf("last read : \"%s\"\n", sh->read);
		free(sh->read);
	}
}
