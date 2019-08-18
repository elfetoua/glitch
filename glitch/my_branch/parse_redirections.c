/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 23:29:05 by aihya             #+#    #+#             */
/*   Updated: 2019/08/01 14:38:45 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

#define LS 1
#define LD 2
#define RS 3
#define RD 4

#define POS_MAX_LEN 1024

typedef struct	s_red
{
	int				type:3;
	char			*right;
	char			*left;
	struct s_red	*next;
}				t_red;

t_red	*red_node(int type, char *right, char *left)
{
	t_red	*node;

	node = (t_red *)malloc(sizeof(t_red));
	node->type = type;
	node->right = right;
	node->left = left;
	node->next = NULL;
	return (node);
}

void	append_red_node(t_red **a_head, t_red *node)
{
	t_red	*curr;

	if (*a_head == NULL)
		*a_head = node;
	else
	{
		curr = *a_head;
		while (curr->next)
			curr = curr->next;
		curr->next = node;
	}
}

int		count_redirect_sym(char *subcmd, int start, char symbol)
{
	int		i;
	int		c;

	c = 0;
	i = start;
	while (subcmd[i] && subcmd[i] == symbol)
	{
		i++;
		c++;
	}
	return (c);
}

void	set_pos_table(int ***pos_table, int index, int pos, int red_type)
{
	(*pos_table)[index] = (int *)malloc(sizeof(int) * 2);
	(*pos_table)[index][0] = pos;
	(*pos_table)[index][1] = red_type;
}

int		append_red_symbol(int ***pos_table, int *c, char *subcmd, int i)
{
	int		k;
	char	sym;

	sym = subcmd[i];
	k = count_redirect_sym(subcmd, i, sym);
	if (k == 1)
		set_pos_table(pos_table, (*c)++, i, (sym == '>' ? RS : LS));
	else if (k == 2)
		set_pos_table(pos_table, (*c)++, i, (sym == '>' ? RD : LD));
	else if (k > 2)
	{
		if (k == 3)
			ft_putendl("parse error near `>'");
		else if (k >= 4)
			ft_putendl("parse error near `>>'");
		pos_table[*c] = NULL;
		return (0);
	}
	return (k);
}

int		**get_red_positions(char *subcmd)
{
	int		i;
	int		j;
	int		c;
	int		**pos_table;

	pos_table = (int **)malloc(sizeof(int *) * POS_MAX_LEN);
	c = 0;
	i = 0;
	while (subcmd[i])
	{
		if (ft_strchr("><", subcmd[i]))
		{
			if ((j = append_red_symbol(&pos_table, &c, subcmd, i)) == 0)
				return (NULL);
			i += j;
			continue ;
		}
		i++;
	}
	return (pos_table);
}

int		is_clean_str(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

t_red	*split_on_reds(char *subcmd, int **red_pos)
{
	int		i;
	int		j;
//	int		c;
//	char	*left;
	char	*right;
	t_red	*head;

	head = NULL;
	i = 0;
	while (red_pos[i])
	{
		if (red_pos[i][1] == RS || red_pos[i][1] == RD)
		{
			right = ft_strnew(0);
			j = red_pos[i][1] == RS ? red_pos[i][0] + 1 : red_pos[i][0] + 2;
			
			
			while (subcmd[j] && subcmd[j] == ' ')
				ft_strappend(&right, subcmd[j++], 1);
			while (subcmd[j] && !ft_strchr("> <\"\';|", subcmd[j]))
				ft_strappend(&right, subcmd[j++], 1);

		//	if (subcmd[j] && ft_strchr("><", subcmd[j]))

			

			/*if (!is_clean_str(right))
				append_red_node(&head, red_node(RS, ft_strdup(right), NULL));
			else if  (red_pos[i + 1])
			{
				ft_putendl("parse error near `\\n'");
				free(right);
				return (NULL);
			}*/


			free(right);
			right = NULL;


		}
		i++;
	}
	return (head);
}

int		main()
{
//	int		i;
//	int		**pos;
	char	str[1024] = "> > > lk";
	/*t_red	*curr;

	i = 0;
	pos = get_red_positions(str);
	if (pos != NULL)
	{
		while (pos[i])
		{
			printf("%d : %d\n", pos[i][0], pos[i][1]);
			i++;
		}
		curr = split_on_reds(str, pos);
		while (curr)
		{
			ft_putendl(curr->right);
			curr = curr->next;
		}
	}*/
	check_cmd(str);
	return (0);
}
