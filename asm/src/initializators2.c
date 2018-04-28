/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializators2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaadia <dsaadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 20:42:21 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/19 14:38:06 by dsaadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

char *reinit_direct(char **dir, int addrnb, int addrline)
{
	char *addrstr;
	int i;

	i = -1;
	if (addrnb < addrline)
		addrnb = 65536 - (addrline - addrnb);
	else
		addrnb = addrnb - addrline;
	addrstr = ft_itoa(addrnb);
	if (!(*dir = (char*)malloc(ft_strlen(addrstr) + 2)))
		return (0);
	(*dir)[0] = '%';
	while (++i < (int)ft_strlen(addrstr))
		(*dir)[i + 1] = addrstr[i];
	(*dir)[i + 1] = 0;
	return (*dir);
}

char *reinit_indirect(char **ind, int addrnb, int addrline)
{
	char *addrstr;
	int i;

	i = -1;
	if (addrnb < addrline)
		addrnb = 65536 - (addrline - addrnb);
	else
		addrnb = addrnb - addrline;
	addrstr = ft_itoa(addrnb);
	if (!(*ind = (char*)malloc(ft_strlen(addrstr) + 1)))
		return (0);
	while (++i < (int)ft_strlen(addrstr))
		(*ind)[i] = addrstr[i];
	(*ind)[i] = 0;
	return (*ind);
}

int init_len_code(void)
{
	t_list	*surf;
	t_list	*new;
	int			cl;

	surf = g_lines;
	while (surf->next)
		surf = surf->next;
	CODE_LEN = LINECONT(surf)->len_tot;
	cl = CODE_LEN;
	surf = g_lines;
	surf = g_lines->next;
	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (0);
	new->content = &cl;
	new->content_size = 4;
	new->next = surf->next;
	surf->next = new;
	return (1);
}

static void alloc_line_zeros(t_line **ln)
{
	(*ln)->len = 0;
	(*ln)->len_tot = 0;
	(*ln)->addr = 0;
	(*ln)->nb_params = 0;
	(*ln)->param = NULL;
}

t_list	*alloc_line(char **spl, char *label, int nbp)
{
	t_line *ln;
	t_list *nw;

	if (!(ln = (t_line*)malloc(sizeof(t_line)))
	|| (!(nw = (t_list*)malloc(sizeof(t_list))) && ft_memdelbool((void**)&ln)))
		return (0);
	if (label)
		LASTC(label) = 0;
	ln->label = label;
	ln->opcode = (nbp > 1) ? fetch_opcode((label) ? spl[1] : spl[0]) : 0;
	alloc_line_zeros(&ln);
	if (nbp > 1)
	{
		ln->nb_params = (label) ? nbp - 2 : nbp - 1;
		ln->param = (label) ? &(spl[2]) : &(spl[1]);
	}
	nw->next = NULL;
	nw->content = ln;
	nw->content_size = 2;
	if (ln->nb_params && !check_params(ln))
		return (0);
	calc_len(ln);
	return (nw);
}