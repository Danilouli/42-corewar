/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_header2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaadia <dsaadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 19:49:44 by dsaadia           #+#    #+#             */
/*   Updated: 2018/05/27 22:23:03 by danielsaadia     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int				have_header_helper(t_list **lst, int fd)
{
	t_list *new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return ((int)super_herror("Malloc error", 0, 0));
	(*lst)->next = new;
	(*lst) = new;
	(*lst)->content_size = 1;
	(*lst)->next = 0;
	if (((*lst)->content = have_truc(fd, NAME_CMD_STRING)) == 0)
		return (0);
	if (ft_strlen((*lst)->content) > PROG_NAME_LENGTH)
		return ((int)super_herror("Name too long", 0, 0));
	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return ((int)super_herror("Malloc error", 0, 0));
	(*lst)->next = new;
	(*lst) = new;
	(*lst)->content_size = 1;
	(*lst)->next = 0;
	if (((*lst)->content = have_truc(fd, COMMENT_CMD_STRING)) == 0)
		return (0);
	if (ft_strlen((*lst)->content) > COMMENT_LENGTH)
		return ((int)super_herror("Comment too long", 0, 0));
	NB_LINES--;
	return (1);
}

int				have_header(int fd)
{
	t_list	*lst;
	int		*magic;

	if (!(magic = (int*)malloc(sizeof(int))))
		return ((int)super_herror("malloc error", 0, 0));
	*magic = COREWAR_EXEC_MAGIC;
	if (!(g_lines = (t_list *)malloc(sizeof(t_list))))
		return ((int)super_herror("malloc error", 0, 0));
	lst = g_lines;
	lst->content_size = 3;
	lst->next = 0;
	lst->content = magic;
	NB_LINES = 1;
	return (have_header_helper(&lst, fd));
}
