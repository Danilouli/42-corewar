/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:33:03 by dsaadia           #+#    #+#             */
/*   Updated: 2018/05/01 22:53:29 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static void	free_g_labels(void)
{
	t_list	*lst;
	t_list	*tmp;
	int		i;

	i = 0;
	lst = g_labels;
	while (lst != NULL)
	{
		tmp = lst->next;
		ft_memdel((void**)&((t_label *)lst->content)->value);
		ft_memdel((void**)&((t_label *)lst->content)->spl);
		ft_memdel(&lst->content);
		ft_memdel((void**)&lst);
		lst = tmp;
	}
	g_labels = NULL;
}

static void	free_g_lines(void)
{
	t_list	*lst;
	t_list	*tmp;
	int		i;

	lst = g_lines;
	while (lst != NULL)
	{
		if (lst->content_size == 2)
		{
			i = 0;
			while (i < ((t_line *)lst->content)->nb_params)
				ft_memdel((void**)&((t_line*)(lst->content))->param[i++]);
			ft_memdel((void**)((t_line*)(lst->content))->param);
			ft_memdel((void**)&((t_line*)(lst->content))->line);
			ft_memdel(&lst->content);
		}
		else if (lst->content_size == 1 || lst->content_size == 3)
			ft_memdel(&lst->content);
		tmp = lst;
		lst = lst->next;
		ft_memdel((void**)&tmp);
	}
	g_lines = NULL;
}

void		free_all(void)
{
	free_g_lines();
	free_g_labels();
}
