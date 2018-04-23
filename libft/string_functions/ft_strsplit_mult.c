/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_mult.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaadia <dsaadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 16:17:32 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/07 20:55:38 by dsaadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Alloue (avec malloc(3)) et retourne un tableau de chaines de caractères
** “fraiches” (toutes terminées par un ’\0’, le tableau également donc)
** résultant de la découpe de s selon n' importe quel caractère de la chaine
** sep. Si l’allocation
** echoue, la fonction retourne NULL.
**
** Exemple : ft_strsplit("*salut*les* gros **etudiants*", ’* ’) renvoie le tableau
** ["salut", "les", "gros" "etudiants"].
*/

static	int		ft_is_sep(char c, char *sep)
{
	if (ft_strchr(sep, c) || c == 0)
		return (1);
	return (0);
}

static size_t	ft_cw(char *s, char *sep)
{
	size_t words;

	words = 0;
	while (*s)
	{
		if (!ft_is_sep(*s, sep) && ft_is_sep(*(s + 1), sep))
			words++;
		s++;
	}
	return (words);
}

static size_t	ft_lensep(char *s, char *sep)
{
	int i;

	i = 0;
	while (!ft_is_sep(*s++, sep))
		i++;
	return (i);
}

static	char	**ft_split(char *s, char *sep, int *nbp)
{
	size_t	i;
	size_t	y;
	char	**res;

	i = 0;
	res = NULL;
	if (!(res = (char**)malloc(ft_cw((char *)s, sep) * (sizeof(char*) + 1))))
		return (NULL);
	while (*s)
	{
		if (!ft_is_sep(*s, sep))
		{
			y = 0;
			if (!(res[i] = (char*)malloc(ft_lensep((char *)s, sep) + 1)))
				return (NULL);
			while (y < ft_lensep((char *)s - y, sep))
				res[i][y++] = *s++;
			res[i++][y] = 0;
		}
		else
			s++;
	}
	res[i] = 0;
	*nbp = i;
	return (res);
}

char			**ft_strsplit_mult(char const *s, char *sep, int *nbp)
{
	char	**res;

	res = NULL;
	if (s && sep && *sep)
		res = ft_split((char*)s, sep, nbp);
	return (res);
}
