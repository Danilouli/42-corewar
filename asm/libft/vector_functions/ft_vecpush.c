/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:49:41 by fsabatie          #+#    #+#             */
/*   Updated: 2018/02/04 13:18:51 by fsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define VS vec->size
#define VB vec->buffer
#define VDS vec->data_size
#define VO vec->occ
#define VR vec->row

t_vec	*ft_vecpush(t_vec *vec, void *data, size_t elem)
{
	size_t		p;
	t_vec		k;

	p = 0;
	k.buffer = vec->buffer;
	if ((VO + (elem * VDS) < VS * VR))
	{
		ft_memcpy(VB + VO, data, elem * VDS);
		VO += elem * VDS;
	}
	else
	{
		if (!(VB = (void*)ft_nrealloc(VB, ++VR * VS, VDS)))
			return (NULL);
		free(k.buffer);
		ft_vecpush(vec, data, elem);
	}
	return (vec);
}
