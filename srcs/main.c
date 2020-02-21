#include "../includes/minishell.h"

void	handle_cmd(t_shell *sh, char **env)
{
	//attention il faut aussi s'occuper des excecutables!!
	if (!ft_strcmp(sh->cmd, "echo"))
		return (handle_echo(sh));
	if (!ft_strcmp(sh->cmd, "cd"))
		return (handle_cd(sh));
	if (!ft_strcmp(sh->cmd, "pwd"))
		return (handle_pwd(sh));
	if (!ft_strcmp(sh->cmd, "exit"))
		return (exit(0));
	if (!ft_strcmp(sh->cmd, "unset"))
		return ;
	if (!ft_strcmp(sh->cmd, "env"))
		return (handle_env(sh, env));
	if (!ft_strcmp(sh->cmd, "export"))
		return ;
	else
		return (handle_bin(sh, env));
}

int	main(int ac, char **av, char **env)
{
	t_shell	*sh;

	if (ac > 0)
	{
		av[1] = 0;
		sh = init_shell();
		ft_printf(PROMPT, "MINISHELL", "file");
		sh->env = env;
		while (get_next_line(0, &sh->read) > 0)
		{
			next_shell(sh);
			parsing_read(sh);
			while (sh->lines[sh->i])
			{
				parsing_line(sh);
				//debug_shell(sh);
				handle_cmd(sh, env);
				sh->i++;
			}
			ft_printf(PROMPT, "MINISHELL", "file");
		}
		printf("last read : \"%s\"\n", sh->read);
		free(sh->read);
	}
}
