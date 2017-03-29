/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 15:14:05 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/29 20:30:44 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*join(char *s1, char *s2, char *s3)
{
	char *tmp;
	char *new;

	tmp = ft_strjoin(s1, s2);
	new = ft_strjoin(tmp, s3);
	ft_strdel(&tmp);
	return (new);
}

char		**utility(char **st, t_env *s_env)
{
	int		i;
	char	*tmp;
	char	**path;
	t_env	*search;

	i = 0;
	search = search_env(s_env, "PATH");
	path = ft_strsplit((join(search->value, ":", _PATH_DEFPATH)), ':');
	while (path[i])
	{
		tmp = path[i];
		path[i] = join(tmp, "/", st[0]);
		ft_strdel(&tmp);
		if ((access(path[i], X_OK)) == 0)
		{
			ft_strdel(&st[0]);
			st[0] = ft_strdup(path[i]);
			ft_strdel(&path[i]);
			return (st);
		}
		ft_strdel(&path[i]);
		i++;
	}
	ft_strdel(path);
	return (st);
}
