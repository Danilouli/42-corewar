/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_x_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:07:33 by acouturi          #+#    #+#             */
/*   Updated: 2018/04/04 15:23:28 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_file	*crea_liste(const int fd, t_file *firstlst)
{
	t_file		*liste;
	t_file		*tmp;

	if (!(liste = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	liste->next = NULL;
	liste->fd = fd;
	tmp = firstlst;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = liste;
	}
	return (liste);
}

static t_file	*crea_chaine(const int fd)
{
	t_file			*liste;
	static t_file	*firstlst = NULL;

	liste = firstlst;
	while (liste)
	{
		if (liste->fd == fd)
			break ;
		liste = liste->next;
	}
	if (!liste)
	{
		if (!(liste = crea_liste(fd, firstlst)))
			return (NULL);
	}
	if (!firstlst)
		firstlst = liste;
	return (liste);
}

int				get_x_char(const int fd, int len, char **line)
{
	char			buffer[len + 1];
	t_file			*liste;

	if (fd < 0 || len < 1 || read(fd, "", 0) == -1)
		return (-1);
	ft_bzero(buffer, len + 1);
	if (!(liste = crea_chaine(fd)))
		return (-1);
	if (read(liste->fd, buffer, len) == 0)
		return (0);
	if (!(*line = (char *)malloc(sizeof(char) * (len + 1))))
		return (-1);
	ft_memcpy((void *)*line, (void *)buffer, len);
	(*line)[len] = 0;
	return (1);
}
