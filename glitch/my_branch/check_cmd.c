/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 17:27:02 by aihya             #+#    #+#             */
/*   Updated: 2019/08/05 18:14:58 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		quote_end(char *cmd, int start)
{
	int		i;
	char	quote;

	quote = cmd[start];
	i = start + 1;
	while (cmd[i] && cmd[i] != quote)
		i++;
	i++;
	return (i);
}

int		count_red(char *cmd, int start, int same)
{
	int		i;
	int		c;

	c = 0;
	i = start;
	if (same)
	{
		while (cmd[i] && cmd[start] == cmd[i])
		{
			i++;
			c++;
		}
	}
	else
	{
		while (cmd[i] && (cmd[i] == '>' || cmd[i] == '<'))
		{
			i++;
			c++;
		}
	}
	return (c);
}

int		error(char *msg)
{
	ft_putendl(msg);
	return (NOK);
}

int		check_counted_red(int c, int lim, char *cmd, int curr)
{
	char	*tmp;
	int		status;

	tmp = ft_strdup("parse error near ");
	if (c > lim)
	{
		ft_strappend(&tmp, cmd[curr], 1);
		ft_strappend(&tmp, cmd[curr + 1], 1);
		status = error(tmp);
		free(tmp);
		return (status);
	}
	else if (lim - 1 == 0 || c > lim - 1)
	{
		ft_strappend(&tmp, cmd[curr], 1);
		status = error(tmp);
		free(tmp);
		return (status);
	}
	return (OK);
}

int		check_quote(char *str, int pos)
{
	int		c;

	if (pos == 0)
		return (OK);
	c = 0;
	while (pos >= 0 && str[pos - 1] == '\\')
	{
		c++;
		pos--;
	}
	if (c % 2 == 0)
		return (OK);
	return (NOK);
}

void	quote_unmatched_err(char quote)
{
	char	*tmp;

	tmp = ft_strdup("Unmatched ");
	ft_strappend(&tmp, quote, 1);
	ft_putendl(tmp);
	ft_strclr(tmp);
	free(tmp);
}
/*
int		check_quotes(char *str)
{
	int		i;
	char	target;

	i = 0;
	while (str[i])
	{
		if ((str[i] == DQUOTE || str[i] == SQUOTE)
				&& check_quote(str, i) && (target = str[i])
				&& (++i))
		{
			while (str[i])
			{
				if (str[i] == target && check_quote(str, i))
					break ;
				i++;
			}
			if (str[i] == target && ++i)
				continue;
			quote_unmatched_err(target);
			return (NOK);
		}
		i++;
	}
	return (OK);
}
*/
int		check_reds(char *cmd)
{
	int		i;
	int		j;
	int		c;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			i = quote_end(cmd, i);
		else if (cmd[i] == '>' || cmd[i] == '<')
		{
			c = count_red(cmd, i, 1);
			if (check_counted_red(c, 3, cmd, i) == 1)
			{
				j = i + c;
				while (cmd[j] && cmd[j] == ' ')
					j++;
				if (!cmd[j])
					return (error("parse error near `\\n'"));
				else if (cmd[j] && (cmd[j] == '>' || cmd[j] == '<'))
					return (check_counted_red(count_red(cmd, j, 0), 1, cmd, j));
				i += c - 1;
			}
			else
				return (NOK);
		}
		i++;
	}
	return (OK);
}
/*
int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char	cmd[] = "echo 123 > abc -e -x > abx";
	int		i;
	int		**pos;

	if (check_quotes(cmd) == OK && check_reds(cmd) == OK)
	{
		i = 0;
		pos = get_reds_positions(cmd);
		while (pos[i])
		{
			printf("%d : %d\n", pos[i][0], pos[i][1]);
			i++;
		}
	}
	return (0);
}*/
