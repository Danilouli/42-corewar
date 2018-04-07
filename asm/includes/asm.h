/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaadia <dsaadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 19:23:12 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/07 15:12:38 by dsaadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include "../../libft/includes/libft.h"

typedef struct		s_line
{
	char			*type;
	char			*label;
	int				op_num;
	char			**param;
}									t_line;

t_list *g_lines;


#endif
