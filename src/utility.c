/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 15:14:05 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/28 19:23:00 by kbagot           ###   ########.fr       */
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

void		make_env(t_env *s_env, char **cstin, t_env *tmp_env)
{
	int i;
	char **var;
	t_env	*save;

	i = 0;
	var = NULL;
	save = s_env;
	tmp_env = s_env;
	while (cstin[i])
	{
		save = tmp_env;
		if (cstin[i] && cstin[i + 1] && ft_strcmp(cstin[i], "env") == 0 && ft_strcmp(cstin[i + 1], "-i") == 0)
		{
			tmp_env = NULL; //leaks land;
			save = tmp_env;
			i++;
		}
		else if (cstin[i] && cstin[i + 1] && ft_strcmp(cstin[i], "env") == 0 && ft_strchr(cstin[i + 1], '='))
		{
			var = ft_strsplit(cstin[i + 1], '=');
			if (tmp_env == NULL)
			{
				tmp_env = ft_memalloc(sizeof(t_env));
				tmp_env->name = ft_strdup(var[0]);
				tmp_env->value = ft_strdup(var[1]);
			}
			else
			add_env(tmp_env, var);
			save = tmp_env;
			i++;
		}
		else if (cstin[i] && ft_strcmp(cstin[i], "env") == 0 && !cstin[i + 1])
		{
			while (save)
			{
				ft_printf("%s=%s\n", save->name, save->value);
				save = save->next;
			}
		}
		else
			break;
		//IF ACCCES continue  else PRin error env
		i++;
	}
	cstin = &cstin[i];
	s_env = save;
}

int			master_env(t_env *s_env, char **cstin, t_env *tmp_env)
{
	int	retvalue;
	int		i;

	i = 0;
	retvalue = 0;
	if (cstin[i] && ((ft_strcmp(cstin[i], "env")) == 0))
	{
		make_env(s_env, &cstin[i], tmp_env);
		retvalue = 1;
	}

	//a deplacer dans builtin
	if (cstin[i] && ((ft_strcmp(cstin[i], "unsetenv")) == 0))
	{
		if (cstin[i + 1])
		{
			delete_env(s_env, cstin[i + 1]);
			retvalue = 1;
			cstin = &cstin[i + 1];
		}
	}
	if (cstin[i] && ((ft_strcmp(cstin[i], "setenv")) == 0))
		if (cstin[i + 1])
		{
			add_env(s_env, &cstin[i + 1]);
			retvalue = 1;
		}
	return (retvalue);
}
