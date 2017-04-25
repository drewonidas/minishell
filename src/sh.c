/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdlamini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 17:42:43 by mdlamini          #+#    #+#             */
/*   Updated: 2016/07/10 17:48:45 by mdlamini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char				*join_path(const char *path, const char *command)
{
	char			*new;

	new = ft_strnew(ft_strlen(path) + ft_strlen(command) + 1);
	new = ft_strcpy(new, path);
	new = ft_strcat(new, "/");
	new = ft_strcat(new, command);
	return (new);
}

void				run(t_sh *sh)
{
	int				sig;
	int				result;
	int				c;
	char			*tmp;

	tmp = NULL;
	sig = 0;
	result = -1;
	c = 0;
	sh->child = fork();
	if (sh->child > 0)
		wait(&sig);
	if (sh->child == 0)
	{
		if (ft_strchr(sh->cmd[0], '/') == NULL)
		{
			while (sh->com_locations[c] && result == -1)
			{
				tmp  = join_path((const char *)sh->com_locations[c++], (const char *)sh->cmd[0]);
				result = execve(tmp, sh->cmd, sh->env_var);
				ft_strdel(&tmp);
			}
		}
		else
			result = execve(sh->cmd[0], sh->cmd, sh->env_var);
		if (result == -1)
			printf("mDash: %s: command not found\n", sh->cmd[0]);
		kill(sh->child, EXIT_SUCCESS);
	}
}

int					minishell(t_sh *sh)
{
	ft_putstr("@>>> ");
	sh->cmd = getcmd();
	if (sh->cmd[0] != NULL)
	{
		if (ft_strcmp("env", sh->cmd[0]) == 0)
			run_env(sh);
		else if (ft_strcmp("echo", sh->cmd[0]) == 0)
			echo_word(sh);
		else if (ft_strcmp("cd", sh->cmd[0]) == 0)
			change_dir(sh);
		else if ((ft_strcmp("exit", sh->cmd[0])) == 0)
		{
			exit_sh(sh);
			return (0);
		}
		else if (sh->cmd[0] != NULL)
			run(sh);
	}
	if (sh->cmd != NULL)
		ft_arrdel(&sh->cmd);
	return (1);
}

int					main(void)
{
	extern	char	**environ;
	t_sh			*sh;

	sh = (t_sh *)malloc(sizeof(t_sh));
	init_sh(sh, environ);
	while (1)
	{
		if (!minishell(sh))
		 break ;
	}
	ft_putendl("Shell terminated!");
	return (0);
}
