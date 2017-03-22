/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 20:58:40 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/22 20:24:15 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_utility(char **env, char **stin)
{
	pid_t	pid;

	if (stin[0][0] != '.' && stin[0][0] != '/')
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(stin[0], 2);
		ft_putchar('\n');
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		if ((execve(stin[0], stin, env)) == -1)
			exit(0);
	}
	else
		wait(NULL);
}
void	parse_entry(t_env *s_env, char **cstin, char *stin)
{
	if (builtin(cstin, s_env, stin) == 0) // cd / echo /exit 
	{
		make_env(s_env, cstin);// env // unsetenv // setenv
		if ((cstin = utility(cstin, s_env)))
			exec_utility(list_to_tab(s_env), cstin);
	}
}
