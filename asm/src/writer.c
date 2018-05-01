/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 22:30:32 by dsaadia           #+#    #+#             */
/*   Updated: 2018/05/01 18:54:53 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int			create_open_cor(char *spath, int fds)
{
	char			*corname;
	char			*sname;
	int				fdc;
  int       len;

	sname = 0;
	(void)fds;
  sname = spath;
  corname = ft_strnew(ft_strlen(sname) + 2);
	corname = ft_strcpy(corname, sname);
  len = ft_strlen(corname) + 2;
  corname[len - 3] = 'c';
  corname[len - 2] = 'o';
  corname[len - 1] = 'r';
  if (corname && (fdc = open(corname, O_WRONLY | O_CREAT | O_TRUNC, 420)) > 0)
  {
    ft_strdel(&corname);
    return (fdc);
  }
  else
  {
    ft_strdel(&corname);
		return (-1);
  }
}

void write_magic(int fdc, int *magic)
{
	int 		tmp;

	tmp = *magic;
	*magic = ((tmp>>24)&0xff) | ((tmp<<8)&0xff0000) | ((tmp>>8)&0xff00) | ((tmp<<24)&0xff000000);
	write(fdc, magic, 4);
	return ;
}

void write_name(int fdc, char *name)
{
	char		*zer_to_write;
	size_t	len;

	len = ft_strlen(name);
	zer_to_write = ft_strnew(PROG_NAME_LENGTH + 4 - len);
	write(fdc, name, len);
	write(fdc, zer_to_write, PROG_NAME_LENGTH + 4 - len);
	ft_strdel(&zer_to_write);
}

void write_len_code(int fdc, int *len_code)
{
	int 		tmp;

	tmp = *len_code;
	*len_code = ((tmp>>24)&0xff) | ((tmp<<8)&0xff0000) | ((tmp>>8)&0xff00) | ((tmp<<24)&0xff000000);
	write(fdc, len_code, 4);
}

void write_comment(int fdc, char *comment)
{
	char		*zer_to_write;
	size_t	len;

	len = ft_strlen(comment);
	zer_to_write = ft_strnew(COMMENT_LENGTH + 4 - len);
	write(fdc, comment, len);
	write(fdc, zer_to_write, COMMENT_LENGTH + 4 - len);
	ft_strdel(&zer_to_write);
}
