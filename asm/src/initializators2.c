/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializators2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 20:42:21 by dsaadia           #+#    #+#             */
/*   Updated: 2018/05/29 18:33:49 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

char		*reinit_direct(char **dir, int addrnb, int addrline)
{
	char	*addrstr;
	int		i;

	i = -1;
	if (addrnb == -2)
		addrnb = CODE_LEN - addrline;
	else if (addrnb < addrline)
		addrnb = 65536 - (addrline - addrnb);
	else
		addrnb = addrnb - addrline;
	addrstr = ft_itoa(addrnb);
	if (!(*dir = (char*)malloc(ft_strlen(addrstr) + 2)))
		return (super_herror("Malloc error", 0, 0));
	(*dir)[0] = '%';
	while (++i < (int)ft_strlen(addrstr))
		(*dir)[i + 1] = addrstr[i];
	ft_memdel((void**)&addrstr);
	(*dir)[i + 1] = 0;
	return (*dir);
}

char		*reinit_indirect(char **ind, int addrnb, int addrline)
{
	char	*addrstr;
	int		i;

	i = -1;
	if (addrnb == -2)
		addrnb = CODE_LEN - addrline;
	else if (addrnb < addrline)
		addrnb = 65536 - (addrline - addrnb);
	else
		addrnb = addrnb - addrline;
	addrstr = ft_itoa(addrnb);
	if (!(*ind = (char*)malloc(ft_strlen(addrstr) + 1)))
		return (super_herror("Malloc error", 0, 0));
	while (++i < (int)ft_strlen(addrstr))
		(*ind)[i] = addrstr[i];
	ft_memdel((void**)&addrstr);
	(*ind)[i] = 0;
	return (*ind);
}

int			init_len_code(void)
{
	t_list	*surf;
	t_list	*new;
	int		cl;

	surf = g_lines;
	while (surf->next)
		surf = surf->next;
	if (surf->content_size == 2)
		CODE_LEN = LINECONT(surf)->len_tot;
	else
		CODE_LEN = 0;
	cl = CODE_LEN;
	surf = g_lines;
	surf = g_lines->next;
	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return ((int)super_herror("Malloc error", 0, 0));
	new->content = &cl;
	new->content_size = 4;
	new->next = surf->next;
	surf->next = new;
	return (1);
}

static void	alloc_line_zeros(t_line **ln)
{
	(*ln)->len = 0;
	(*ln)->len_tot = 0;
	(*ln)->addr = 0;
	(*ln)->nb_params = 0;
	(*ln)->param = NULL;
}

t_list		*alloc_line(char **spl, char *label, int nbp, char *l)
{
	t_line		*ln;
	t_list		*nw;
	int			cp;

	cp = 0;
	if (!(ln = (t_line*)malloc(sizeof(t_line)))
	|| (!(nw = (t_list*)malloc(sizeof(t_list))) && ft_memdelbool((void**)&ln)))
		return (super_herror("Malloc error", 0, 0));
	ln->label = label;
	ln->line = l;
	if (!(ln->opcode = 0) && nbp > 1)
		ln->opcode = fetch_opcode((label) ? spl[1] : spl[0]);
	alloc_line_zeros(&ln);
	if ((ln->nb_line = NB_LINES) >= 0 && nbp > 1)
	{
		ln->nb_params = (label) ? nbp - 2 : nbp - 1;
		ln->param = (label) ? &(spl[2]) : &(spl[1]);
		(LAST_LABEL) ? redefine_labels(LAST_LABEL) : LAST_LABEL;
	}
	alloc_line_helper(&nw, ln);
	if (ln->nb_params && (cp = check_params(ln)) >= 0)
		return (super_herror("Invalid parameter for instruction",
		cp, g_op_tab[ln->opcode - 1].name));
		calc_len(ln);
	return (nw);
}
