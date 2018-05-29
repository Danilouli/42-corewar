/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:17:43 by fsabatie          #+#    #+#             */
/*   Updated: 2018/05/29 18:45:12 by vlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

short			getintvertices(float iv[][3], t_map *map)
{
	short i;
	short counter;

	i = 0;
	counter = 0;
	while (i < 4096)
	{
		if (map->p_map[i])
		{
			iv[counter][0] = i % 64;
			iv[counter][1] = i / 64;
			iv[counter++][2] = 2;
		}
		i++;
	}
	return (counter);
}

void			assign_color(float **v, float r, float g, float b)
{
	float *inner;

	inner = *v;
	*inner++ = r;
	*inner++ = g;
	*inner++ = b;
	*v = inner;
}

void			getcolor(float **v, t_map *map, float x, float y)
{
	float *inner;

	inner = *v;
	if (map->c_map[(int)(x + (y * 64))] == 1)
		assign_color(&inner, (float)0.945, (float)0.082, (float)0.082);
	else if (map->c_map[(int)(x + (y * 64))] == 2)
		assign_color(&inner, (float)0.8, (float)0.0, (float)0.8);
	else if (map->c_map[(int)(x + (y * 64))] == 3)
		assign_color(&inner, (float)0.0, (float)1.0, (float)0.0);
	else if (map->c_map[(int)(x + (y * 64))] == 4)
		assign_color(&inner, (float)0.0, (float)1.0, (float)1.0);
	else if (map->c_map[(int)(x + (y * 64))] == 0)
		assign_color(&inner, (float)0.6, (float)0.6, (float)0.6);
	*v = inner;
}

void			getcoord(float **v, t_map *map, float x, float y)
{
	float *inner;

	inner = *v;
	*inner++ = x / 64 - 0.5;
	*inner++ = y / 64 - 0.5;
	*inner++ = map->style ?
	interpolation(map->ctrl_pts, map->int_vert, x, y) / 64
	: (float)(map->p_map[(int)x + ((int)y * 64)] / (float)64);
	getcolor(&inner, map, x, y);
	*v = inner;
}

void			getmap(float *v, t_map *map)
{
	float			x;
	float			y;

	y = 0;
	while (y < 63.0)
	{
		x = 1;
		while (x < 64.0)
		{
			getcoord(&v, map, x, y);
			getcoord(&v, map, x - 1, y);
			getcoord(&v, map, x - 1, y + 1);
			getcoord(&v, map, x, y);
			getcoord(&v, map, x, y + 1);
			getcoord(&v, map, x - 1, y + 1);
			x++;
		}
		y++;
	}
}
