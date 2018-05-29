/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:34:45 by acouturi          #+#    #+#             */
/*   Updated: 2018/05/29 15:58:34 by dsaadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

char		*testempty(char *tmp)
{
	int		i;

	i = 0;
	while (tmp[i] == ' ' || tmp[i] == '\t')
		i++;
	ft_memmove(tmp, &tmp[i], ft_strlen(tmp));
	if (tmp[0] == 0 || tmp[0] == ';' || tmp[0] == COMMENT_CHAR)
		ft_memdel((void **)&tmp);
	return (tmp);
}

char		*is_onlyspace(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	if ((tmp = ft_strchr(str, '"')) == 0)
		return (0);
	while (str[i] != *tmp)
	{
		if (str[i] != ' ' && *str != '\t')
		{
			ft_strdel(&str);
			return (0);
		}
		i++;
	}
	tmp = ft_strdup(tmp + 1);
	ft_strdel(&str);
	return (tmp);
}

char		*have_truc_helper(char *tmp, char *truc, int fd)
{
	char	*ret;
	int		i;

	if ((ret = is_onlyspace(ft_strdup(&tmp[ft_strlen(truc)]))) == 0)
	{
		ft_strdel(&tmp);
		return (super_herror("No char : \" in header", ft_strlen(truc), 0));
	}
	i = (((int)destroy(&tmp) & NB_LINES++)) & 0;
	while (ft_strcount(ret, '"') != 1)
	{
		if ((ft_strcount(ret, '"') > 1 && !super_herror("Invalid file", 0, 0))
			|| (get_next_line(fd, &tmp) != 1 &&
			super_herror("Error while reading file", 0, 0) == 0))
			return (NULL);
		ret = ft_strjoinfree(ret, "\n");
		ret = ft_strjoinfree(ret, tmp);
		i = ((int)destroy(&tmp) & NB_LINES++) & 0;
	}
	tmp = ft_strchr(ret, '"');
	tmp[0] = 0;
	while ((++i) >= 0 && tmp[i] && tmp[i] != '#')
		if (tmp[i] != ' ' && tmp[i] != '\n')
			return (super_herror("Invalid file", 0, 0));
	return (ret);
}

char		*have_truc(int fd, char *truc)
{
	char	*tmp;

	tmp = NULL;
	while (tmp == NULL && ++NB_LINES)
	{
		if (get_next_line(fd, &tmp) != 1)
			return (super_herror("Empty file", 0, 0));
		tmp = testempty(tmp);
	}
	NB_LINES--;
	if ((ft_strncmp(truc, tmp, ft_strlen(truc))))
	{
		ft_strdel(&tmp);
		return (super_herror("Invalid file", 0, 0));
	}
	return (have_truc_helper(tmp, truc, fd));
}
