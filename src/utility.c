/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 15:14:05 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/23 20:11:23 by kbagot           ###   ########.fr       */
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

char	**utility(char **st, t_env *s_env)
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

int		builtin(char **cstin, t_env *env, char *stin)
{
	t_env *search;
	// cd // echo // exit
	if (cstin[0])
	{
		if (ft_strcmp(cstin[0], "exit") == 0)
		{
			if (cstin[1])
				exit(ft_atoi(cstin[1]));
			else
				exit(0);
			return (1);
		}

		if (ft_strcmp(cstin[0], "cd") == 0)
		{
			if (cstin[1])
			{
				if ((chdir(cstin[1])) == -1)
					return (1);
				else if ((ft_strcmp(cstin[1], "~") == 0))
				{
					search = search_env(env, "HOME");
					chdir(search->value);
				}
			}
			else
			{
				search = search_env(env, "HOME");
				chdir(search->value);
			}
			search = search_env(env, "PWD");
			ft_strdel(&search->value);
			search->value = ft_strnew(PATH_MAX);
			getcwd(search->value, PATH_MAX);
			search->value = ft_strjoin("PWD=", search->value);
			return (1);
		}
/////////////		
		int i;
		int space;
		int	cot;

		cot = 0;
		space = 0;
		i = 5;
		if (ft_strcmp(cstin[0], "echo") == 0)
		{
			while (stin[i])
			{
				if (stin[i] == 39 || stin[i] == 34)
					cot++;
				if (!stin[i])
					break;
				i++;
			}
			if (cot % 2 != 0)
			{
				ft_putstr_fd("quote ", 2);
				ft_putchar('\n');
				return (1);
			}
		////////
			i = 5;
			cot = 0;
			space = 0;
			while (stin[i])
			{
				if (stin[i] == 39 || stin[i] == 34)
				{
					if (cot == 0)
						cot = 1;
					else
						cot = 0;
					i++;
					if (stin[i - 1] == stin[i])
					{
						cot = 0;
						i++;
					}
					if (!stin[i])
						break;
				}
			////////////
				if (cot == 0 && stin[i] == ' ')
				{
					while (stin[i] && stin[i] == ' ')
						i++;
					i--;
				}
				ft_putchar(stin[i]);
				i++;
			}
			ft_putchar('\n');
			return (1);
		}
	}
	return (0);
}

int		make_env(t_env *s_env, char **cstin)
{
	int	retvalue;
	int		i;
	t_env	*tmp;

	i = 0;
	retvalue = 0;
	tmp = s_env;
	while (cstin[i])
	{
		if (cstin[i] && ((ft_strcmp(cstin[i], "env")) == 0))
		{
			while (s_env)
			{
				ft_printf("%s=%s\n", s_env->name, s_env->value);
				s_env = s_env->next;
			}
			s_env = tmp;
			retvalue = 1;
		}
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
		i++;
	}
	printf("lol\n");
	return (retvalue);
}
