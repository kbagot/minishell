/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 20:58:40 by kbagot            #+#    #+#             */
/*   Updated: 2017/04/03 20:04:37 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	invalid_exec(char **stin , char **env)
{
	if ((stin[0] && stin[0][0] != '.' && stin[0][0] != '/') || !stin[0])
	{
		ft_tabdel(env);
		if (stin[0])
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putstr_fd(stin[0], 2);
			ft_putchar_fd('\n', 2);
		}
		return (1);
	}
	return (0);
}

void		exec_utility(char **env, char **stin, t_data *data)
{
	pid_t	pid;
	int		rvalue;

	rvalue = 0;
	if (invalid_exec(stin, env))
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (execve(stin[0], stin, env) == -1)
				exit(1);
	}
	else
	{
		wait(&rvalue);
		data->rvalue = WEXITSTATUS(rvalue);

	}
	ft_tabdel(env);
}

void		parse_entry(t_env *s_env, char **cstin, char *stin, t_data *data)
{
	t_env	*tmp_env;
	t_env	*save;

	tmp_env = NULL;
	if ((data->rvalue = builtin(cstin, s_env, stin, data)))// cd / echo /exit  /unsetenv/ setenv
		return ;
	tmp_env = master_env(s_env, cstin, tmp_env);// env
	if ((cstin = utility(cstin, s_env)))
		exec_utility(list_to_tab(tmp_env), cstin, data);
	destroy_env(&tmp_env);
}
