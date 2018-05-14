/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verificators.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaadia <dsaadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 16:03:39 by dsaadia           #+#    #+#             */
/*   Updated: 2018/05/14 10:24:37 by danielsaadia     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int	is_label(char *str)
{
	size_t i;

	i = 0;
	if (LASTC(str) != LABEL_CHAR)
		return (0);
	while (str[i])
	{
		if (!ft_strchr(LABEL_CHARS, str[i]) && (i < ft_strlen(str) - 1))
			return (0);
		i++;
	}
	return (1);
}

int	is_op_name(char *str)
{
	int i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (ft_strequ(str, g_op_tab[i].name))
			return (1);
		i++;
	}
	return (0);
}

int	check_param(t_line *line, int i)
{
	int		par;
	int		comp;

	par = what_is(line->param[i]);
	comp = LINEOP.param[i];
	return (par & comp);
}

int	check_params(t_line *line)
{
	int i;

	i = 0;
	while (i < line->nb_params)
		i++;
	if (i != g_op_tab[line->opcode - 1].nb_p)
		return (0);
	i = 0;
	while (i < g_op_tab[line->opcode - 1].nb_p)
	{
		if (!check_param(line, i))
			return (i);
		i++;
	}
	return (-1);
}
