/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 20:58:40 by kbagot            #+#    #+#             */
/*   Updated: 2017/04/02 22:17:42 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_utility(char **env, char **stin)
{
	pid_t	pid;

	if (stin[0] && stin[0][0] != '.' && stin[0][0] != '/')
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(stin[0], 2);
		ft_putchar_fd('\n', 2);
		ft_tabdel(env);
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
	ft_tabdel(env);
}

void	parse_entry(t_env *s_env, char **cstin, char *stin)
{
	t_env *tmp_env;
	t_env *save;

	tmp_env = NULL;
	if ((builtin(cstin, s_env, stin)))// cd / echo /exit  /unsetenv/ setenv
		return ;
	tmp_env = master_env(s_env, cstin, tmp_env);// env
	//	printf("%s\n", tmp_env->name);
	if ((cstin = utility(cstin, s_env)))
		exec_utility(list_to_tab(tmp_env), cstin);
	if (tmp_env)
		while (tmp_env)
		{
			ft_strdel(&tmp_env->name);
			ft_strdel(&tmp_env->value);
			save = tmp_env->next;
			free(tmp_env);
			tmp_env = save;
		}
}
