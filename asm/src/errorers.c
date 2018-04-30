/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 15:04:33 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/30 17:04:12 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

void	*super_herror(char *msg, int char_ind)
{
	//g_d_errors->lastmsgerror = msg;
	ft_printf("error : %s\n",msg);
	//g_d_errors->nb_lines = NB_LINES;
	ft_printf("line : %d\n",NB_LINES);
	//g_d_errors->nb_char = char_ind;
	ft_printf("char : %d\n",char_ind);
	g_nberror++;
	return (0);
}

char	*destroy(char **del)
{
	ft_strdel(del);
	*del = NULL;
	return (NULL);
}
