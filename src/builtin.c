/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 16:58:48 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/29 14:58:48 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	exec_exit(char **cstin)
{
	if (cstin[1])
		exit(ft_atoi(cstin[1]));
	else
		exit(0);
	return (1);
}

static void	update_env(t_env *env)
{
	t_env *pwd;
	t_env *oldpwd;

	pwd = search_env(env, "PWD");
	oldpwd = search_env(env, "OLDPWD");
	ft_strdel(&oldpwd->value);
	oldpwd->value = ft_strdup(pwd->value);
	ft_strdel(&pwd->value);
	pwd->value = ft_strnew(PATH_MAX);
	getcwd(pwd->value, PATH_MAX);
}

static int	exec_cd(char **cstin, t_env *env)
{
	t_env	*search;
	int		i;

	i = 0;
	while (cstin[i])
		i++;
	if (i >= 3)
	{
		ft_putstr_fd("cd: Too many arguments\nusage: cd [dir]\n", 2);
		return (1);
	}
	else if (i == 2 &&(chdir(cstin[1])) == -1)
	{
		ft_putstr_fd("cd: No such file or directory\n", 2);
		ft_putstr_fd(cstin[1], 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	else if (i == 1)
	{
		search = search_env(env, "HOME");
		chdir(search->value);
	}
	update_env(env);
	return (1);
}

int			builtin(char **cstin, t_env *env, char *stin)
{
	if (cstin[0])
	{
		if ((ft_strcmp(cstin[0], "exit")) == 0)
			return (exec_exit(cstin));
		else if ((ft_strcmp(cstin[0], "cd")) == 0)
			return (exec_cd(cstin, env));
		else if ((ft_strcmp(cstin[0], "echo")) == 0 && ft_strlen(stin) > 5)
			return (exec_echo(&stin[5]));
		else if (ft_strcmp(cstin[0], "setenv") == 0)
		{
			add_env(env, &cstin[1]);
			return (1);
		}
		else if (ft_strcmp(cstin[0], "unsetenv") == 0)
		{
			delete_env(env, cstin[1]);
			return (1);
		}
	}
	return (0);
}
