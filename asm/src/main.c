/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 19:18:47 by dsaadia           #+#    #+#             */
/*   Updated: 2018/05/31 16:30:53 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static int	main_read(char **av)
{
	int		fd;
	char	*comment;
	char	*l;
	int		fdc;

	g_lines = NULL;
	g_op_tab = init_g_op_tab();
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return ((int)super_herror("File do not exist", 0, 0));
	if (!have_header(fd))
		return (0);
	while (get_next_line(fd, &l) == 1 && ((NB_LINES++) >= 0))
	{
		if ((comment = ft_strchr(l, COMMENT_CHAR)))
			comment[0] = 0;
		else if ((comment = ft_strchr(l, ';')))
			comment[0] = 0;
		if (!read_code(l))
			break ;
	}
	if (!init_len_code() || !is_real_code() ||
		(fdc = create_open_cor(av[1], fd)) < 0)
		return (0);
	return (fdc);
}

static void	main_write(int fdc, int *i, int *title)
{
	if (g_lines->content_size == 4 &&
		(*(int*)(g_lines->content) = CODE_LEN) > -1)
		write_len_code(fdc, (int*)(g_lines->content));
	else if (g_lines->content_size == 3)
		write_magic(fdc, (int*)(g_lines->content));
	else if (g_lines->content_size == 1)
	{
		if (*title)
		{
			write_name(fdc, (char*)(g_lines->content));
			*title = 0;
		}
		else
			write_comment(fdc, (char*)(g_lines->content));
	}
	else if (g_lines->content_size == 2)
	{
		if (((t_line*)g_lines->content)->len)
			write_line(fdc, (t_line*)g_lines->content);
		if (((t_line*)g_lines->content)->nb_params > 0 && !(*i = 0))
			while (*i < g_op_tab[((t_line*)g_lines->content)->opcode - 1].nb_p)
				(*i)++;
	}
	g_lines = g_lines->next;
}

int			main(int ac, char **av)
{
	int		i;
	int		fdc;
	int		title;
	t_list	*keep;

	title = 1;
	g_corewar = init_g_corewar();
	g_labels = NULL;
	i = 1;
	if (ac <= 1)
	{
		ft_printf("Usage: ./asm <sourcefile.s>\n");
		return (1);
	}
	if (!(fdc = main_read(av)))
		return (1);
	i = 0;
	keep = g_lines;
	while (g_lines)
		main_write(fdc, &i, &title);
	g_lines = keep;
	free_all();
	ft_printf("champion créé\n");
	return (0);
}
