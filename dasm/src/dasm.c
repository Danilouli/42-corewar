/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 19:38:19 by acouturi          #+#    #+#             */
/*   Updated: 2018/05/29 16:10:41 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/dasm.h"

static void		add_error(t_error *str_err, char *msg)
{
	ft_strcpy(str_err->lastmsgerror, msg);
	str_err->nberror++;
}

void			get_info(int fdn, int fd)
{
	uintmax_t		lenprog;
	char			*prog;
	char			*data;
	char			*name;
	char			*comment;

	if (get_x_char(fd, PROG_NAME_LENGTH + 4, &name) == 1)
	{
		ft_dprintf(fdn, "%s \"%s\"\n", NAME_CMD_STRING, name);
		if (get_x_char(fd, 4, &data) == 1)
		{
			lenprog = (unsigned char)data[0] * 256 * 256 * 256 +
			(unsigned char)data[1] * 256 * 256 + (unsigned char)data[2] * 256 +
			(unsigned char)data[3];
			if (get_x_char(fd, COMMENT_LENGTH + 4, &comment) == 1)
			{
				ft_dprintf(fdn, "%s \"%s\"\n\n", COMMENT_CMD_STRING, comment);
				if (get_x_char(fd, lenprog, &prog) == 1)
				{
					dasm_code((unsigned char *)prog, fdn, lenprog);
					ft_strdel((char **)&prog);
				}
				ft_strdel(&comment);
			}
			ft_strdel(&data);
		}
		ft_strdel(&name);
	}
}

void			creat_new_file(char *fname, int fd, t_error *str_err)
{
	char			*newname;
	char			*tmp;
	int				fdn;

	newname = ft_strdup(fname);
	if (!ft_strncmp(&newname[ft_strlen(newname) - 4], ".cor", 4))
	{
		ft_strcpy(&newname[ft_strlen(newname) - 3], "s");
		if ((tmp = ft_strrchr(newname, '/')))
			;
		else
			tmp = newname;
		ft_memmove(&tmp[1], tmp, ft_strlen(tmp) + 1);
		tmp[1] = 'd';
		ft_printf("%s\n", newname);
		if (newname &&
				0 < (fdn = open(newname, O_WRONLY | O_CREAT | O_TRUNC, 420)))
		{
			get_info(fdn, fd);
			close(fdn);
		}
		else
			add_error(str_err, "can't create file");
	}
	ft_strdel(&newname);
}

void			test_file(char *fname, t_error *str_err)
{
	char			*data;
	int				fd;

	data = NULL;
	if (0 < (fd = open(fname, O_RDONLY)))
	{
		if (get_x_char(fd, 4, &data) > 0)
		{
			if (COREWAR_EXEC_MAGIC == (unsigned char)data[0] * 256 * 256 * 256 +
			(unsigned char)data[1] * 256 * 256 + (unsigned char)data[2] * 256 +
			(unsigned char)data[3])
				creat_new_file(fname, fd, str_err);
			else
				add_error(str_err, "mauvaise version du fichier(bad magical)");
		}
		else
			add_error(str_err, "file doesn't exist");
		ft_strdel(&data);
		close(fd);
	}
	else
		add_error(str_err, "file doesn't exist");
	ft_strdel(&data);
}

int				main(int argc, char **argv)
{
	t_error			str_err;

	ft_bzero(&str_err, sizeof(t_error));
	if (argc == 2)
		test_file(argv[1], &str_err);
	else
		add_error(&str_err, "error usage :\n./dasm file.cor");
	if (str_err.nberror)
		ft_putendl(str_err.lastmsgerror);
	else
		ft_putendl("File create");
	return (str_err.nberror);
}
