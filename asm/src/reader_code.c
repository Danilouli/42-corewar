/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaadia <dsaadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:49:01 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/25 18:24:17 by dsaadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static int change_line_if_needed_help(char **l, int *i)
{
	while ((*l)[*i])
	{
		if ((*l)[*i] == ' ' || (*l)[*i] == '\t')
			return (1);
		if (((*l)[*i] == DIRECT_CHAR || (*l)[*i] == LABEL_CHAR )
		&& (*l)[*i + 1] && (*l)[*i + 1] != ' ' && (*l)[*i + 1] != '\t')
			return (0);
		(*i)++;
	}
	return (0);
}

static int change_line_if_needed(char **l)
{
	int 	i;
	char	*new;
	int		j;

	i = 0;
	new = 0;
	j = -1;
	while ((*l)[i] == ' ' || (*l)[i] == '\t')
		i++;
	if (change_line_if_needed_help(l, &i))
		return (1);
	if (!(*l)[i])
		return (1);
	if (!(new = (char*)malloc(ft_strlen(*l) + 2)))
		return (0);
	while (++j < i)
		new[j] = (*l)[j];
	new[j] = ' ';
	new[j + 1] = 0;
	ft_strcpy(&(new[j + 1]), &((*l)[i]));
	ft_strdel(l);
	*l = ft_strdup(new);
	ft_strdel(&new);
	return (1);
}

int read_code_helper(char **spl, int nbp, t_list **new)
{
	t_list	*newla = NULL;
	t_label *labeq = NULL;

	newla =  (t_list*)malloc(sizeof(t_list));
	labeq = (t_label*)malloc(sizeof(t_label));
	if (is_label(spl[0]))
	{
		labeq->value = spl[0];
		labeq->real_label = spl[0];
		labeq->addr = 0;
		newla->next = NULL;
		newla->content = labeq;
		newla->content_size = 5;
		// if (!(newla = alloc_label(spl[0])))
		// 	return (0);
		ft_lstpushback(g_labels, newla);
		if ((nbp > 1 && !is_op_name(spl[1]))) //|| (super_herror("OPCODE NUL\n",58)))
			return (0);
		if (nbp > 1)
		{
			if (!(*new = alloc_line(spl, spl[0], nbp)))
				return (0);
			ft_lstpushback(g_lines, *new);
		}
		else if(!(LASTC(spl[0]) = 0))
			LAST_LABEL = spl[0];
	}
	else if (!is_label(spl[0]) && is_op_name(spl[0]))
	{
		if (!is_op_name(spl[0]) || !(*new = alloc_line(spl, 0, nbp)))
			return (0);
		ft_lstpushback(g_lines, *new);
	}
	else
		return (0);
	return (1);
}

int	read_code(char *l)
{
	char 		**spl;
	t_list	*new;
	int			nbp;

	new = NULL;
	init_g_seps();
	change_line_if_needed(&l);
	spl = ft_strsplit_mult(l, g_seps, &nbp);
	if (!nbp)
		return (1);
	if (!read_code_helper(spl, nbp, &new))
		return (0);
	return (1);
}
