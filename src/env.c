/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 19:41:17 by kbagot            #+#    #+#             */
/*   Updated: 2017/04/02 19:18:04 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_env(char **cstin, t_env *tmp_env)
{
	while (tmp_env)
	{
		ft_printf("%s=%s\n", tmp_env->name, tmp_env->value);
		tmp_env = tmp_env->next;
	}
	swap_dat(cstin, 1);
}

static void	addtmp_env(char **cstin, t_env **tmp_env)
{
	char **var;

	var = ft_strsplit(cstin[1], '=');
	if (*tmp_env == NULL)
	{
		*tmp_env = ft_memalloc(sizeof(t_env));
		(*tmp_env)->name = ft_strdup(var[0]);
		(*tmp_env)->value = ft_strdup(var[1]);
	}
	else if (var)
		add_env(*tmp_env, var);
	swap_dat(cstin, 2);
}

static void	clean_env(t_env **tmp_env, char **cstin)
{
	t_env	*save;

	if (tmp_env)
		while (*tmp_env)
		{
			ft_strdel(&(*tmp_env)->name);
			ft_strdel(&(*tmp_env)->value);
			save = (*tmp_env)->next;
			free(*tmp_env);
			*tmp_env = save;
		}
	swap_dat(cstin, 2);
}

static void	make_env(char **cstin, t_env **tmp_env)
{
	while (cstin[0])
	{
		if (cstin[0] && cstin[1] && ft_strcmp(cstin[0], "env") == 0 &&
				ft_strcmp(cstin[1], "-i") == 0)
			clean_env(tmp_env, cstin);
		else if (cstin[0] && cstin[1] && ft_strcmp(cstin[0], "env") == 0 &&
				ft_strchr(cstin[1], '='))
			addtmp_env(cstin, tmp_env);
		else if (cstin[0] && ft_strcmp(cstin[0], "env") == 0 && !cstin[1])
		{
			print_env(cstin, *tmp_env);
			break ;
		}
		else if (cstin[0] && ft_strcmp(cstin[0], "env") == 0)
		{
			swap_dat(cstin, 1);
			break ;
		}
		else
			break ;
	}
}

t_env		*master_env(t_env *s_env, char **cstin, t_env *tmp_env)
{
	char **var;

	var = list_to_tab(s_env);
	tmp_env = env_build(var, tmp_env);
	if (cstin[0] && ((ft_strcmp(cstin[0], "env")) == 0))
		make_env(cstin, &tmp_env);
	ft_tabdel(var);
	return (tmp_env);
}
