/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 14:36:14 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/29 20:30:48 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*env_build(char **env, t_env *first_env)
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
		if ((ft_strcmp(new_env->name, "SHLVL")) == 0)
			new_env->value = ft_strdup(ft_itoa(ft_atoi(&env[i][j + 1]) + 1));
		else if ((ft_strcmp(new_env->name, "SHELL")) == 0)
			new_env->value = ft_strdup("~/Documents/Projet/minishell/minishell");  /////////////////////
		else
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
void	delete_env(t_env *env, char *name)
{
	t_env *bef;

	bef = NULL;
	while (env)
	{
		if ((ft_strcmp(env->name, name)) == 0)
		{
			bef->next = env->next;
			ft_strdel(&env->name);
			ft_strdel(&env->value);
			free(env);
			env = NULL;
			return;
		}
		bef = env;
		env = env->next;
	}
}

void	add_env(t_env *env, char **cstin)
{
	t_env	*search;

	search = search_env(env, cstin[0]);
	if (search && cstin[0])
	{
		ft_strdel(&search->value);
		search->value = ft_strdup(cstin[1]);
		return;
	}
	while (env->next)
		env = env->next;
	if (cstin[0])
	{
		env->next = ft_memalloc(sizeof(t_env));
		env->next->name = ft_strdup(cstin[0]);
		if (cstin[1])
			env->next->value = ft_strdup(cstin[1]);
		else
			env->next->value = ft_strnew(1);
	}
	else
	{
		ft_putstr_fd("usage: setenv [name=value ...]\n", 2);
	//	ft_putchar('\n');
	}
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
/*
char		*unsplit(char **dt)
{
	int		i;
	char	*new;
	char	*unleaks;

	i = 0;
	printf("66666%s\n", dt[2]);
	unleaks = ft_strdup(dt[0]);
	if (!dt[1])
		return (unleaks);
	while (dt[i])
	{
		new = ft_strjoin(unleaks, dt[i]);
		ft_strdel(&unleaks);
		i++;
	}
	printf("%s\n", new);
	return (new);
}
*/

static void set(char **str, t_env *env)
{
	t_env *search;
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i][0] == '$' && str[i][1])
		{
			search = search_env(env, &str[i][1]);
			if (search)
			{
				ft_strdel(&str[i]);
				str[i] = ft_strdup(search->value);
			}
			else
			{
				ft_strdel(&str[i]);
				str[i] = ft_strnew(1);
			}
		}
		i++;
	}
}

static void show_prompt(t_env *s_env, char **env)
{
	char	*stin;
	char	**cstin;
	t_env	*search;
	int		i;

	i = 0;
	stin = NULL;
	search = search_env(s_env, "PWD");
	ft_printf("\033[0;36m[%s]> \033[0m", &(ft_strrchr(search->value, '/')[1]));
	get_next_line(0, &stin);
	cstin = ft_strsplit(stin, ' ');
	set(cstin, s_env);
	parse_entry(s_env, cstin, stin);
	ft_strdel(&stin);
	if (s_env)
		show_prompt(s_env, env);
}

int		main(int ac, char **av, char **env)
{
	t_env	*s_env;

	if (ac == 1)
	{
		av = NULL;
		s_env = NULL;
		s_env = env_build(env, s_env);
		show_prompt(s_env, env);
	}
	else
		ft_putstr_fd("minishell: can't open input file\nusage: minishell", 2);
	return(0);
}
