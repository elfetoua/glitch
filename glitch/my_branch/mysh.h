/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mysh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 15:24:07 by aihya             #+#    #+#             */
/*   Updated: 2019/08/02 18:14:42 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSH_H
# define MYSH_H

#include "libft.h"
#include <stdio.h>

# define OK 1
# define NOK 0
# define TRUE 1
# define FALSE 0

# define SQUOTE '\''
# define DQUOTE '\"'
# define DOLLAR '$'
# define TILDE '~'

# define ALNUM "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789"

# define LS 0
# define LD 1
# define RS 2
# define RD 3

# define FNAME 0
# define FDESC 1

# define POS_MAX_LEN 1024

typedef struct	s_red
{
	char			*right;
	char			*left;
	int				type:2;
	int				r_type:1;
	int				l_type:1;
	struct s_red	*next;
}				t_red;

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

int     quote_end(char *cmd, int start);
int     count_red(char *cmd, int start, int same);
int     **get_reds_positions(char *cmd);
t_env	*ms_init_env(char **ev);
int		ms_env(t_env *env);
char	**ms_expand_args(char **args, t_env *env);
char    *ms_expand_tilde(char *arg, t_env *env);
char    *ms_expand_dollars(char *arg, t_env *env);
char    *ms_expand_quotes(char *arg);
char    *ms_expand_arg(char *arg, t_env *env);
t_env	*ms_node(char *name, char *value);
t_env   *ms_get_var(char *name, t_env *env);
void	ms_free_node(t_env **node);

#endif
