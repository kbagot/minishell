/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 16:58:48 by kbagot            #+#    #+#             */
/*   Updated: 2017/04/02 22:17:38 by kbagot           ###   ########.fr       */
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
	if (oldpwd)
	{
		ft_strdel(&oldpwd->value);
		oldpwd->value = ft_strdup(pwd->value);
	}
	if (pwd)
	{
		ft_strdel(&pwd->value);
		pwd->value = ft_strnew(PATH_MAX);
		getcwd(pwd->value, PATH_MAX);
	}
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
	else if (i == 2 && (chdir(cstin[1])) == -1)
	{
		ft_putstr_fd("cd: No such file or directory\n", 2);
		ft_putstr_fd(cstin[1], 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	else if (i == 1 && (search = search_env(env, "HOME")))
		chdir(search->value);
	update_env(env);
	return (1);
}

static int	exec_env(char **cstin, t_env *env, char *stin)
{
	if (cstin[0] && ft_strcmp(cstin[0], "setenv") == 0)
	{
		if (cstin[1] && cstin[2] && cstin[3])
			ft_putstr_fd("setenv: Too many arguments\n", 2);
		else if (cstin[1])
			add_env(env, &cstin[1]);
		else
			ft_putstr_fd("setenv: Too few arguments\n", 2);
	}
	else if (cstin[0] && ft_strcmp(cstin[0], "unsetenv") == 0)
	{
		if (cstin[1])
			delete_env(env, cstin[1]);
		else
			ft_putstr_fd("unsetenv: Too few arguments\n", 2);
	}
	return (1);
}

int			builtin(char **cstin, t_env *env, char *stin)
{
	if (cstin[0] && (ft_strcmp(cstin[0], "exit") == 0))
	{
		ft_strdel(&stin);
		return (exec_exit(cstin));
	}
	else if (cstin[0] && (ft_strcmp(cstin[0], "cd") == 0))
		return (exec_cd(cstin, env));
	else if (cstin[0] && (ft_strcmp(cstin[0], "echo") == 0 &&
				ft_strlen(stin) > 5))
		return (exec_echo(&stin[5]));
	else if (cstin[0] && ((ft_strcmp(cstin[0], "setenv") == 0) ||
			ft_strcmp(cstin[0], "unsetenv") == 0))
		return (exec_env(cstin, env, stin));
	return (0);
}
