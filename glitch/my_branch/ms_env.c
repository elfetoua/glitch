/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:35:09 by aihya             #+#    #+#             */
/*   Updated: 2019/08/02 11:10:09 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ms_env(t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		ft_putstr(curr->name);
		ft_putchar('=');
		ft_putendl(curr->value);
		curr = curr->next;
	}
	return (OK);
}
