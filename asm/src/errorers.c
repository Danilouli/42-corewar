/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaadia <dsaadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 15:04:33 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/29 16:00:37 by dsaadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

void	*super_herror(char *msg, int char_ind)
{
	g_d_errors->lastmsgerror = msg;
	g_d_errors->nb_lines = NB_LINES;
	g_d_errors->nb_char = char_ind;
	g_d_errors->nberror++;
	return (0);
}

char	*destroy(char **del)
{
	ft_strdel(del);
	*del = NULL;
	return (NULL);
}
