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

char		*trim_quotes(char const *s)
{
	char	*new;
	int		i;

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
