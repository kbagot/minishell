/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 15:14:05 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/31 15:32:52 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*join(char *s1, char *s2, char *s3)
{
	char *tmp;
	char *new;

	tmp = ft_strjoin(s1, s2);
	ft_strdel(&s1);
	new = ft_strjoin(tmp, s3);
	ft_strdel(&tmp);
	return (new);
}

char		**utility(char **st, t_env *s_env)
{
	int		i;
	char	**path;
	t_env	*search;

	i = 0;
	if ((search = search_env(s_env, "PATH")))
		path = ft_strsplit((join(ft_strdup(search->value), ":",
						_PATH_DEFPATH)), ':');
	else
		path = ft_strsplit(_PATH_DEFPATH, ':');
	while (path[i])
	{
		path[i] = join(path[i], "/", st[0]);
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
