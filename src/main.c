/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 14:36:14 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/21 19:04:02 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_env	*env_build(char **env, t_env *first_env)
{
	t_env	*bef_env;
	t_env	*new_env;
	int		i;
	int		j;

	j = 0;
	i = 0;
	bef_env = NULL;
	while (env[i])
	{
		new_env = (t_env*)malloc(sizeof(t_env));
		if (i == 0)
			first_env = new_env;
		if (bef_env)
			bef_env->next = new_env;
		while (env[i][j] && env[i][j] != '=')
			j++;
		new_env->name = ft_strsub(env[i], 0, j);
		new_env->value = ft_strsub(env[i], j + 1, ft_strlen(env[i]) - j);
		j = 0;
		bef_env = new_env;
		new_env->next = NULL;
		i++;
	}
	return (first_env);
}

char **list_to_tab(t_env *lenv)
{
	char	*env;
	char	*tmp;

	tmp = NULL;
	env = ft_strnew(1);
	while (lenv)
	{
		tmp = ft_strjoin(env, lenv->name);
		ft_strdel(&env);
		env	= ft_strjoin(tmp, "=");
		ft_strdel(&tmp);
		tmp = ft_strjoin(env, lenv->value);
		ft_strdel(&env);
		env = ft_strjoin(tmp, " ");
		ft_strdel(&tmp);
		lenv = lenv->next;
	}
	return (ft_strsplit(env, ' '));
}

t_env *search_env(t_env *env, char *name)
{
	while (env)
	{
		if ((ft_strcmp(env->name, name)) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static void show_prompt(t_env *s_env, char **env)
{
	char *stin;
	char **cstin;
	t_env *search;

	stin = NULL;
	search = search_env(s_env, "PWD");
	ft_printf("\033[0;36m[%s]> \033[0m", &(ft_strrchr(search->value, '/')[1]));
	get_next_line(0, &stin);
	cstin = ft_strsplit(stin, ' ');
	parse_entry(s_env, cstin, stin); // inbuilt or bin
	ft_strdel(&stin);
	show_prompt(s_env, env);
}

int		main(int ac, char **av, char **env)
{
	char	*prompt;
	t_env	*s_env;
	char	**test;

	s_env = NULL;
	prompt = NULL;
	s_env = env_build(env, s_env);
	test = list_to_tab(s_env);
	show_prompt(s_env, env);
	return(0);
}
