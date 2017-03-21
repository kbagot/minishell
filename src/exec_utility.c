/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 20:58:40 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/21 19:04:04 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_utility(char **env, char **stin)
{
	pid_t pid;

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
		if ((cstin = utility(cstin, s_env)))
			exec_utility(list_to_tab(s_env), cstin);
	}
}
