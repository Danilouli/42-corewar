/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verificators2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 19:31:57 by dsaadia           #+#    #+#             */
/*   Updated: 2018/05/31 15:46:33 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static int	is_cor_strnum(char *str)
{
	int i;

	i = 0;
	if (!ft_isdigit(str[0]) && str[0] != '-')
		return (0);
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

static int	is_cor_label(char *str)
{
	int i;

	i = 0;
	if (str[0] != LABEL_CHAR)
		return (0);
	while (str[++i])
	{
		if (!ft_strchr(LABEL_CHARS, str[i]))
			return (0);
	}
	return (1);
}

int			is_direct(char *str)
{
	if (str[0] != DIRECT_CHAR)
		return (0);
	if (!is_cor_label(str + 1) && !is_cor_strnum(str + 1))
		return (0);
	return (1);
}

int			is_reg(char *str)
{
	int regn;

	if (str[0] != 'r')
		return (0);
	regn = ft_atoi(str + 1);
	if (0 < regn && regn <= REG_NUMBER && is_cor_strnum(str + 1))
		return (1);
	return (0);
}

int			is_indirect(char *str)
{
	if (!is_cor_label(str) && !is_cor_strnum(str))
		return (0);
	return (1);
}
