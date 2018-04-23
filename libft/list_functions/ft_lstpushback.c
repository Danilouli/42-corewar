/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 12:51:35 by fsabatie          #+#    #+#             */
/*   Updated: 2018/04/07 21:49:50 by dsaadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Ajoute l’élément new en fin de liste.
*/

void	ft_lstpushback(t_list *start, t_list *new)
{
	if (!start)
	{
		start = new;
		return ;
	}
	while (start->next != NULL)
		start = start->next;
	start->next = new;
}
