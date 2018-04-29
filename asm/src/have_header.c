/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:34:45 by acouturi          #+#    #+#             */
/*   Updated: 2018/04/29 16:01:30 by dsaadia          ###   ########.fr       */
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

	if ((tmp = ft_strchr(str, '"')) == 0)
		return (0);
	while (str != tmp)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (tmp + 1);
}

char		*have_truc(int fd, char *truc)
{
	char	*ret;
	char	*tmp;
	int		i;

	tmp = NULL;
	while (tmp == NULL && ++NB_LINES)
	{
		if (get_next_line(fd, &tmp) != 1)
			return(super_herror("fichier vide\n", 0));
		tmp = testempty(tmp);
	}
	NB_LINES--;
	if ((ft_strncmp(truc, tmp, ft_strlen(truc))))
		return (super_herror("fichier non valide\n", 0));
	ret = is_onlyspace(ft_strdup(&tmp[ft_strlen(truc)]));
	i = (((int)destroy(&tmp) & NB_LINES++)) & 0;
	while (ft_strcount(ret, '"') != 1)
	{
		if ((ft_strcount(ret, '"') > 1 && super_herror("fichier non valide\n", 0) == 0)
		|| (get_next_line(fd, &tmp) != 1 && super_herror("probleme lecture\n", 0) == 0))
			return (NULL);
		ret = ft_strjoinfree(ret, "\n");
		ret = ft_strjoinfree(ret, tmp);
		i = ((int)destroy(&tmp) & NB_LINES++) & 0;
	}
	tmp = ft_strchr(ret, '"');
	tmp[0] = 0;
	i = 0;
	while ((++i) >= 0 && tmp[i] && tmp[i] != '#')
		if (tmp[i] != ' ' && tmp[i] != '\n')
			return (super_herror("fichier non valide\n", 0));
	return (ret);
}

int				have_header(int fd)
{
	t_list	*lst;
	t_list	*new;
	int		*magic;

	if (!(magic = (int*)malloc(sizeof(int))))
		return ((int)super_herror("malloc error\n", 0));
	*magic = COREWAR_EXEC_MAGIC;
	if (!(g_lines = (t_list *)malloc(sizeof(t_list))))
		return ((int)super_herror("malloc error\n", 0));
	lst = g_lines;
	lst->content_size = 3;
	lst->next = 0;
	lst->content = magic;
	NB_LINES = 1;
	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return ((int)super_herror("malloc error\n", 0));
	lst->next = new;
	lst = new;
	lst->content_size = 1;
	lst->next = 0;
	lst->content = have_truc(fd, NAME_CMD_STRING);
	if (g_d_errors->nberror > 0)
		return (0);
	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return ((int)super_herror("malloc error\n", 0));
	lst->next = new;
	lst = new;
	lst->content_size = 1;
	lst->next = 0;
	lst->content = have_truc(fd, COMMENT_CMD_STRING);
	if (g_d_errors->nberror > 0)
		return (0);
	return (1);
}
