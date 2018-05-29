/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaadia <dsaadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 15:04:33 by dsaadia           #+#    #+#             */
/*   Updated: 2018/05/29 17:23:49 by dsaadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

void	*super_herror(char *msg, int ind, char *clue)
{
	if (clue)
		ft_printf("Error :	%s %s\n", msg, clue);
	else
		ft_printf("Error :	%s\n", msg);
	if (NB_LINES)
		ft_printf("	At line number : %d\n", NB_LINES);
	if (ft_strstr(msg, "parameter"))
		ft_printf("	For parameter number : %d\n", ind);
	else
		ft_printf("	At char number : %d\n", ind);
	exit(0);
}

char	*destroy(char **del)
{
	ft_strdel(del);
	*del = NULL;
	return (NULL);
}

int		gce(char *err_word, char *l)
{
	char *err_op;

	if (!(err_op = ft_strstr(l, err_word)))
		return (-1);
	return ((int)(err_op - l) + 1);
}
