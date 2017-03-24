/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 20:14:48 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/24 20:47:13 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <paths.h>
# include <limits.h>

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct	s_env	*next;
}					t_env;

void				exec_utility(char **env, char **stin);
void				parse_entry(t_env *s_env, char **cstin, char *stin);
t_env				*search_env(t_env *env, char *name);
char				**list_to_tab(t_env *lenv);
int					builtin(char **cstin, t_env *env, char *stin);
char				**utility(char **st, t_env *s_env);
int					make_env(t_env *s_env, char **cstin);
void				delete_env(t_env *env, char *name);
void				add_env(t_env *env, char **cstin);
int					exec_echo(char *stin);
char				*unsplit(char **dt);

#endif
