/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:34:45 by acouturi          #+#    #+#             */
/*   Updated: 2018/04/29 19:09:40 by acouturi         ###   ########.fr       */
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
		{
			return(super_herror("fichier vide", 0));
		}
		tmp = testempty(tmp);
	}
	NB_LINES--;
	if ((ft_strncmp(truc, tmp, ft_strlen(truc))))
		return (super_herror("fichier non valide", 0));
	if ((ret = is_onlyspace(ft_strdup(&tmp[ft_strlen(truc)]))) == 0)
		return (super_herror("pas de caractere : \"", ft_strlen(truc)));
	i = (((int)destroy(&tmp) & NB_LINES++)) & 0;
	while (ft_strcount(ret, '"') != 1)
	{
		if ((ft_strcount(ret, '"') > 1 && super_herror("fichier non valide", 0) == 0)
		|| (get_next_line(fd, &tmp) != 1 && super_herror("probleme lecture", 0) == 0))
			return (NULL);
		ret = ft_strjoin(ret, "\n");			//mettre joinfree
		ret = ft_strjoin(ret, tmp);				//idem
		i = ((int)destroy(&tmp) & NB_LINES++) & 0;
	}
	tmp = ft_strchr(ret, '"');
	tmp[0] = 0;
	i = 0;
	while ((++i) >= 0 && tmp[i] && tmp[i] != '#')
		if (tmp[i] != ' ' && tmp[i] != '\n')
			return (super_herror("fichier non valide", 0));
	return (ret);
}

int				have_header(int fd)
{
	t_list	*lst;
	t_list	*new;
	int		*magic;

	if (!(magic = (int*)malloc(sizeof(int))))
		return ((int)super_herror("malloc error", 0));
	*magic = COREWAR_EXEC_MAGIC;
	if (!(g_lines = (t_list *)malloc(sizeof(t_list))))
		return ((int)super_herror("malloc error", 0));
	lst = g_lines;
	lst->content_size = 3;
	lst->next = 0;
	lst->content = magic;
	NB_LINES = 1;
	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return ((int)super_herror("malloc error", 0));
	lst->next = new;
	lst = new;
	lst->content_size = 1;
	lst->next = 0;
	if ((lst->content = have_truc(fd, NAME_CMD_STRING)) == 0)
		return (0);
	if (ft_strlen(lst->content) > PROG_NAME_LENGTH)
		return ((int)super_herror("name too long", 0));
	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return ((int)super_herror("malloc error", 0));
	lst->next = new;
	lst = new;
	lst->content_size = 1;
	lst->next = 0;
	if ((lst->content = have_truc(fd, COMMENT_CMD_STRING)) == 0)
		return (0);
	if (ft_strlen(lst->content) > COMMENT_LENGTH)
		return ((int)super_herror("comment too long", 0));
	NB_LINES--;
	return (1);
}
