/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:34:10 by exam              #+#    #+#             */
/*   Updated: 2019/07/15 16:29:03 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <limits.h>

char    g_base_conv_chars[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

long long	ll_abs(long long n)
{
	return (n >= 0 ? n : (-1) * n);
}

char		*convert_to_base(long long value, int base)
{
	int			i;
	int			sign;
	char		buffer[66];
	long long	n;

	n = value;
	sign = 0;
	if (sign > 0)
		sign = 1;
	i = 0;
	while (n == LLONG_MIN || ll_abs(n) >= base)
	{
		buffer[i] = g_base_conv_chars[ll_abs(n % base)];
		n = n / base;
		i++;
	}
	buffer[i++] = g_base_conv_chars[ll_abs(n)];
	if (sign == 1)
		buffer[i++] = '-';
	buffer[i] = '\0';
	return (ft_strdup(buffer));
}

char		*ft_itoa_base(long long value, int base)
{
	char	*res;
	char	*buffer;
	int		len;
	int		j;

	len = (int)ft_strlen(buffer);
	buffer = convert_to_base(value, base);
	res = (char *)malloc(sizeof(char) * (len + 1));
	len--;
	j = 0;
	while (len >= 0)
	{
		res[j] = buffer[len];
		len--;
		j++;
	}
	res[j] = '\0';
	return (res);
}
