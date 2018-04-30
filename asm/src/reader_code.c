/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaadia <dsaadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:49:01 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/30 17:51:14 by dsaadia          ###   ########.fr       */
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
		return ((int)super_herror("malloc error\n", 0));
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

int read_code_helper(char **spl, int nbp, t_list **new, char *l)
{
	t_list	*newla = NULL;

	if (is_label(spl[0]))
	{
		LASTC(spl[0]) = 0;
		LAST_LABEL = spl[0];
		if (!(newla = alloc_label(spl[0])))
			return (0);
		if (!g_labels)
			g_labels = newla;
		else
			ft_lstpushback(g_labels, newla);
		if ((nbp > 1 && !is_op_name(spl[1])))
			return ((int)super_herror("OPCODE invalide", 42) & 0);
		if (nbp > 1)
		{
			if (!(*new = alloc_line(spl, spl[0], nbp, l)))
				return (0);
			ft_lstpushback(g_lines, *new);
		}
	}
	else if (!is_label(spl[0]) && is_op_name(spl[0]))
	{
		if (!is_op_name(spl[0]) || !(*new = alloc_line(spl, 0, nbp, l)))
			return ((int)super_herror("OPCODE invalide", 42) & 0);
		ft_lstpushback(g_lines, *new);
	}
	else
		return ((int)super_herror("OPCODE invalide", 42) & 0);
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
	return (read_code_helper(spl, nbp, &new, l));
}
