/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaadia <dsaadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 15:04:33 by dsaadia           #+#    #+#             */
/*   Updated: 2018/05/14 10:13:21 by danielsaadia     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

void	*super_herror(char *msg, int char_ind)
{
	ft_printf("error : %s\n", msg);
	ft_printf("line : %d\n", NB_LINES);
	ft_printf("char : %d\n", char_ind);
	g_nberror++;
	return (0);
}

char	*destroy(char **del)
{
	ft_strdel(del);
	*del = NULL;
	return (NULL);
}

int gce(char *err_word, char *l)
{
	if (!ft_strstr(l, err_word))
		return (-1);
	ft_printf("passe->%s--ori->%s\n",ft_strstr(l, err_word),l);
	return ((int)(ft_strstr(l, err_word) - l) + 1);
}
