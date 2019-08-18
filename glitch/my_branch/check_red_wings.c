/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_red_wings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 16:16:32 by aihya             #+#    #+#             */
/*   Updated: 2019/08/02 14:22:51 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		check_right_wing(t_red *node)
{
	char	*res;
	int		i;
	int		j;

	res = NULL;
	i = 0;
	if (node->right[i] == ' ')
	{
		node->r_type = FNAME;
		while (node->right[i] && node->right[i] == ' ')
			i++;
		res = ft_strdup(str + i);
		free(node->right);
		node->right = res;
	}
	else if (node->right[i] == '&')
	{
		if (ft_isdigit(node->right[i + 1]))
		{
			j = i + 1;
			while (ft_isdigit(node->right[j]))
				j++;
			if (node->right[j] == ' ')
				node->r_type = FDESC;
		}
	}
}

int		check_left_wing(t_red *node)
{
	
}

int		check_red_wings(t_red *node)
{
	if (check_right_wing(node) == NOK || check_left_wing(node) == NOK)
		return (NOK);
	return (OK);
}
