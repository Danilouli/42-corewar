/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:13:06 by acouturi          #+#    #+#             */
/*   Updated: 2018/05/01 15:05:55 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_lenitoa(int n)
{
	int		len;
	long	tmp;

	len = 0;
	tmp = n;
	if (n < 0)
	{
		len++;
		tmp = -tmp;
	}
	if (tmp == 0)
		len++;
	while (tmp)
	{
		tmp /= 10;
		len++;
	}
	return (len);
}

static char		*ft_retmin(char *ret)
{
	ret[0] = '-';
	ret[1] = '2';
	ret[2] = '1';
	ret[3] = '4';
	ret[4] = '7';
	ret[5] = '4';
	ret[6] = '8';
	ret[7] = '3';
	ret[8] = '6';
	ret[9] = '4';
	ret[10] = '8';
	return (ret);
}

char			*ft_itoa(int n)
{
	int		signe;
	int		len;
	long	tmp;
	char	*ret;

	if (n < 0)
		signe = -1;
	else
		signe = 1;
	len = ft_lenitoa(n);
	tmp = n * signe;
	ret = (char*)malloc((len + 1) * sizeof(char));
	if (ret == 0)
		return (0);
	ret[len--] = 0;
	if (n == -2147483648)
		return (ft_retmin(ret));
	while (len >= 0)
	{
		ret[len--] = tmp % 10 + '0';
		tmp /= 10;
	}
	if (signe < 0)
		ret[0] = '-';
	return (ret);
}
