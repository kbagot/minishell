/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 20:58:40 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/31 18:23:29 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_utility(char **env, char **stin)
{
	pid_t	pid;

//	printf("%s\n", stin[0]);
	if (stin[0] && stin[0][0] != '.' && stin[0][0] != '/')
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(stin[0], 2);
		ft_putchar_fd('\n', 2);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(stin[0], stin, env) == -1)
			exit(1);
	}
	else
		wait(NULL);
}

void	parse_entry(t_env *s_env, char **cstin, char *stin)
{
	t_env *tmp_env;

	tmp_env = NULL;
	if ((builtin(cstin, s_env, stin)))// cd / echo /exit  /unsetenv/ setenv
		return ;
	master_env(s_env, cstin, tmp_env);// env
	if ((cstin = utility(cstin, s_env)))
		exec_utility(list_to_tab(tmp_env), cstin);
}
