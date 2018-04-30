/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 19:18:47 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/30 16:56:06 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int	main2(int ac, char **av)
{
	int		i;
	int		fd;
	int		fdc;
	char	*l;
	char	*comment;
	int title;

	title = 1;
	g_nberror = 0;
	g_corewar = init_g_corewar();
	g_labels = NULL;
	i = 1;
	if (ac <= 1)
	{
		ft_printf("Usage: ./asm [-a] <sourcefile.s>\n	-a : Instead of creating a \
.cor file, outputs a stripped and annotated version of \
the code to the standard output");
		return (1);
	}
	g_lines = NULL;
	g_op_tab = init_g_op_tab();
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return ((int)super_herror("files do not exist", 0));
	if (!have_header(fd))
		return (1);
	while (get_next_line(fd, &l) == 1 && ((NB_LINES++) >= 0))
	{
		if ((comment =  ft_strchr(l, COMMENT_CHAR)))
			comment[0] = 0;
		else if ((comment =  ft_strchr(l, ';')))
			comment[0] = 0;
		if (!read_code(l))
			break ;
	}
	if (g_nberror >= 1)
		return (1);
	if (!init_len_code())
		return (1);
	if (!is_real_code())
		return (1);
	if ((fdc = create_open_cor(av[1], fd)) < 0)
		return (1);
	i = 0;
	t_list *keep = g_lines;
	while (g_labels)
	{
		g_labels = g_labels->next;
	}
	while (g_lines)
	{
		if (g_lines->content_size == 4)
		{
			*(int*)(g_lines->content) = CODE_LEN;
			write_len_code(fdc, (int*)(g_lines->content));
		}
		else if (g_lines->content_size == 3)
			write_magic(fdc, (int*)(g_lines->content));
		else if (g_lines->content_size == 1)
		{
			if (title)
			{
				write_name(fdc, (char*)(g_lines->content));
				title = 0;
			}
			else
				write_comment(fdc, (char*)(g_lines->content));
		}
		else if (g_lines->content_size == 2)
		{
			if (((t_line*)g_lines->content)->len)
				write_line(fdc, (t_line*)g_lines->content);
			if (((t_line*)g_lines->content)->nb_params > 0)
			{
				i = 0;
				while (i < g_op_tab[((t_line*)g_lines->content)->opcode - 1].nb_p)
					i++;
			}
		}
		g_lines = g_lines->next;
	}
	g_lines = keep;
	// free_g_line();
	ft_printf("champion créé\n");
	return (0);
}

int	main(int ac, char **av)
{
	main2(ac, av);
	ft_printf("end\n");
	while (42)
		;
	return (0);
}