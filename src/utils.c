/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdlamini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 17:49:38 by mdlamini          #+#    #+#             */
/*   Updated: 2016/07/10 17:54:22 by mdlamini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <stdio.h>

int 		change(t_sh *sh, char *new_dir)
{
	int 	j;
	int		result;
	char	*cwd;
	char	*tmp;
	
	result = 0;
	j = find(sh->env_var, "PWD");
	cwd = ft_strnew(ft_strlen(sh->env_var[j]));
	cwd = getcwd(cwd, ft_strlen(sh->env_var[j]));
	tmp = join_path(cwd, new_dir);
	result = chdir((const char *)tmp);
	ft_strdel(&cwd);
	ft_strdel(&tmp);
	return (result);
}

void		get_home(t_sh *sh, char **dir)
{
	int		i;
	char	*tmp;
	char	*new_dir;
	
	i = find(sh->env_var, "HOME");
	new_dir = *dir;
	if (ft_strlen(new_dir) > 1)
		tmp = join_path(ft_strchr(sh->env_var[i], '/'), &new_dir[1]);
	else
		tmp = ft_strdup(ft_strchr(sh->env_var[i], '/'));
	ft_strdel(dir);
	*dir = tmp;
}

// TODO: change cd ~ to work with any directory e.g cd ~/Documents
void		change_dir(t_sh *sh)
{
	int		result;
	int		cnt;
	char	*new_dir;

	cnt = 0;
	new_dir = NULL;
	result = 0;
	while (sh->cmd[cnt])
		cnt++;
	if (cnt < 2)
		new_dir = ft_strdup("~");
	else
		new_dir = ft_strdup((const char *)sh->cmd[1]);
	if (new_dir[0] == '~')
		get_home(sh, &new_dir);
	if (new_dir[0] == '/')
		result = chdir((const char *)new_dir);
	else
		result = change(sh, new_dir);
	if (result == -1)
		printf("mDash: %s: no such file or directory\n", new_dir);
	ft_strdel(&new_dir);
}

void		exit_sh(t_sh *sh)
{
	pid_t	tmp;

	tmp = sh->child;
	if (sh->cmd != NULL) 
		ft_arrdel(&sh->cmd);
	if (sh->env_var != NULL)
		ft_arrdel(&sh->env_var);
	if (sh->com_locations != NULL)
		ft_arrdel(&sh->com_locations);
	if (sh->env_var_bckp != NULL)
		ft_arrdel(&sh->env_var_bckp);
	free(sh);
	sh = NULL;
	if (tmp)
		kill(tmp, SIGTERM);
//	exit(0);
}

void		print_env(char **env)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
		ft_putendl(env[i++]);
}

void		set_env(char *name, t_sh *sh)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	tmp = ft_strsub(name, 0, indexof(name, '='));
	i = find(sh->env_var, tmp);
	free(tmp);
	if (i == -1)
	{
		sh->env_var[sh->env_size] = ft_strdup(name);
	}
	else
	{
		ft_strdel(&sh->env_var[i]);
		sh->env_var[i] = ft_strdup(name);
	}
}

void		unset_env(t_sh *sh)
{
	ft_arrdel(&sh->env_var);
	sh->env_var = ft_arrdup(sh->env_var_bckp);
}

char				*trim_quotes(char const *s)
{
	char			*new;
	int				i;

	i = 0;
	new = NULL;
	if (s != NULL)
	{
		while ((*s == '"' || *s == '\'') && (*s != '\0'))
			s++;
		i = ft_strlen(s) - 1;
		if (i <= 0)
			return (NULL);
		while ((s[i] == '"' || s[i] == '\'') && (i))
			i--;
		new = ft_strnew(++i);
		if (new != NULL)
		{
			new = ft_strncpy(new, s, i);
			return (new);
		}
	}
	return (NULL);
}

void		echo_word(t_sh *sh)
{
	int		i;
	int		b;
	char	*tmp;

	i = 1;
	b = -1;
	tmp = NULL;
	if (sh->cmd[i] != NULL)
	{
		while (sh->cmd[i] != NULL)
		{
			if (ft_strchr(sh->cmd[i], '"'))
				tmp = trim_quotes((char const *)sh->cmd[i]);
			else
				tmp = ft_strdup(sh->cmd[i]);
			if (tmp[0] == '$')
				b = find(sh->env_var, &tmp[1]);
			if (b != -1)
				ft_putstr(sh->env_var[b]);
			else if (b == -1 && ft_strcmp("$", tmp) == 0)
				ft_putstr(tmp);
			ft_putchar(' ');
			if (tmp != NULL)
				ft_strdel(&tmp);
			i++;
			b = -1;
		}
	}
	ft_putchar('\n');
}
