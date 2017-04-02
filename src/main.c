/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 14:36:14 by kbagot            #+#    #+#             */
/*   Updated: 2017/04/02 22:17:44 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void		ms_dat(t_env *new_env, char **env, int i, int j)
{
	if ((ft_strcmp(new_env->name, "SHELL")) == 0)
		new_env->value = ft_strdup("~/Documents/Projet/minishell/minishell");
	else
		new_env->value = ft_strsub(env[i], j + 1, ft_strlen(env[i]) - j);
}

t_env			*env_build(char **env, t_env *first_env)
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
		ms_dat(new_env, env, i, j);
		j = 0;
		bef_env = new_env;
		new_env->next = NULL;
		i++;
	}
	return (first_env);
}

static void		set(char **str, t_env *env)
{
	t_env	*search;
	int		i;

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

static void		show_prompt(t_env *s_env, char **env)
{
	char	*stin;
	char	**cstin;
	t_env	*search;
	int		i;

	i = 0;
	stin = NULL;
	if ((search = search_env(s_env, "PWD")))
		ft_printf("\033[0;36m[%s]> \033[0m",
				&(ft_strrchr(search->value, '/')[1]));
	else
		ft_printf("\033[0;36m[]> \033[0m");
	get_next_line(0, &stin);
	cstin = ft_strsplit(stin, ' ');
	set(cstin, s_env);
	parse_entry(s_env, cstin, stin);
	ft_strdel(&stin);
	ft_tabdel(cstin);
	if (s_env || !s_env)
		show_prompt(s_env, env);
}

int				main(int ac, char **av, char **env)
{
	t_env	*s_env;
	t_env	*search;
	char	*tmp;

	search = NULL;
	if (ac == 1)
	{
		av = NULL;
		s_env = NULL;
		s_env = env_build(env, s_env);
		if ((search = search_env(s_env, "SHLVL")))
		{
			tmp = search->value;
			search->value = ft_itoa(ft_atoi(tmp) + 1);
			ft_strdel(&tmp);
		}
		show_prompt(s_env, env);
	}
	else
		ft_putstr_fd("minishell: can't open input file\nusage: minishell", 2);
	if (s_env)
		while (s_env)
		{
			ft_strdel(&s_env->name);
			ft_strdel(&s_env->value);
			search = s_env->next;
			free(s_env);
			s_env = search;
		}
	return (0);
}
