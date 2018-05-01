/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:33:03 by dsaadia           #+#    #+#             */
/*   Updated: 2018/05/01 16:03:40 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

void free_g_line(void)
{
	t_list	*lst;
	t_list	*tmp;
	int		i;

	//ft_printf("%p\n", lst);
	lst = g_lines;
	//*
	while(lst != NULL)
	{
		//ft_printf("%p %d %p\n", lst, lst->content_size, lst->content);
		if (lst->content_size == 2)
		{
			i = 0;
			//ft_printf("a\n");
			while (i < ((t_line *)lst->content)->nb_params)
				ft_memdel((void**)&((t_line*)(lst->content))->param[i++]);
			//ft_printf("b\n");
			ft_memdel((void**)((t_line*)(lst->content))->param);
			//ft_printf("c\n");
			ft_memdel((void**)&((t_line*)(lst->content))->line);
			//ft_printf("d\n");
			ft_memdel(&lst->content);
		}
		else if (lst->content_size == 1 || lst->content_size == 3)
		{
			//ft_printf("%s\n", lst->content);
			ft_memdel(&lst->content);
		}
		tmp = lst;
		lst = lst->next;
		ft_memdel((void**)&tmp);
	}
	g_lines = NULL;

	i = 0;
	lst = g_labels;
	while (lst != NULL)
	{
		//ft_printf("FREE %p--%s\n", ((t_label *)lst->content)->value,((t_label *)lst->content)->value);
		tmp = lst->next;
		// free(((t_label *)lst->content)->value);
		ft_memdel((void**)&((t_label *)lst->content)->value);
		ft_printf("DEL %p\n",((t_label *)lst->content)->spl);
		ft_memdel((void**)&((t_label *)lst->content)->spl);
		ft_memdel(&lst->content);
		ft_memdel((void**)&lst);
		lst = tmp;
	}
	g_labels = NULL;
	//*/
}
