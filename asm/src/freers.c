/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaadia <dsaadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:33:03 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/19 15:40:13 by dsaadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

void free_g_line(void)
{
    t_list  *lst;
    t_list  *tmp;
    int     i;
    lst = g_lines;
    while(lst != NULL)
    {
        if (lst->content_size == 2)
        {
            ft_memdel((void**)((t_line*)(lst->content))->label);
            i = 0;
            while ((void**)((t_line*)(lst->content))->param[i])
                ft_memdel((void**)((t_line*)(lst->content))->param[i++]);
            ft_memdel((void**)((t_line*)(lst->content))->param);
            ft_memdel(lst->content);
        }
        else if (lst->content_size == 1)
            ft_memdel(lst->content);
        tmp = lst;
        lst = lst->next;
        ft_memdel((void**)tmp);
    }
}
