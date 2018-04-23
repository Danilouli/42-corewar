/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaadia <dsaadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 15:04:33 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/08 15:13:50 by dsaadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int				add_error(t_error *str_err, char *msg)
{
	str_err->lastmsgerror = msg;
	str_err->nberror++;
	return (0);
}

char		*destroy(char **del)
{
	ft_strdel(del);
	*del = NULL;
	return (NULL);
}
