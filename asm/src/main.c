/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 19:18:47 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/29 19:19:38 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

//*

int	main(int ac, char **av)
{
	int		i;
	int		fd;
	int		fdc;
	char	*l;
	char	*comment;
	int title;

	title = 1;
	g_d_errors = init_g_d_errors();
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
	if (!have_header(fd))// && ft_printf("%s\n",g_d_errors->lastmsgerror))
		return (1);
	while (get_next_line(fd, &l) == 1 && ((NB_LINES++) >= 0))
	{
		// ft_printf("DHQIHDOIQHFIOQH->%s--%d\n", l, NB_LINES);
		if ((comment =  ft_strchr(l, COMMENT_CHAR)))
			comment[0] = 0;
		else if ((comment =  ft_strchr(l, ';')))
			comment[0] = 0;
		if (!read_code(l))
			break ;
	}
	if (g_d_errors->nberror >= 1)
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
		//ft_printf("LABEL :::: %s, son REAL %s\n",((t_label*)(g_labels->content))->value, ((t_label*)(g_labels->content))->real_label);
		g_labels = g_labels->next;
	}
	while (g_lines)
	{
		if (g_lines->content_size == 4)
		{
			*(int*)(g_lines->content) = CODE_LEN;
			//ft_printf("Taille prog %d--%d\n", *(int*)(g_lines->content), CODE_LEN);
			write_len_code(fdc, (int*)(g_lines->content));
		}
		else if (g_lines->content_size == 3)
		{
			//ft_printf("Magic %x\n", *(int*)(g_lines->content));
			write_magic(fdc, (int*)(g_lines->content));
		}
		else if (g_lines->content_size == 1)
		{
			//ft_printf("NAME OU COMMENT %s\n",(char*)(g_lines->content));
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
			//ft_printf("label %s, ",((t_line*)g_lines->content)->label);
			//ft_printf("len %d len_tot %d addr %d | ",((t_line*)g_lines->content)->len,
			//((t_line*)g_lines->content)->len_tot, ((t_line*)g_lines->content)->addr);
			if (((t_line*)g_lines->content)->nb_params > 0)
			{
				//ft_printf("opcode %d, operation %s --> ",((t_line*)g_lines->content)->opcode,g_op_tab[((t_line*)g_lines->content)->opcode - 1].name);
				i = 0;
				//ft_printf("nb params %d, ", LINECONT(g_lines)->nb_params);
				while (i < g_op_tab[((t_line*)g_lines->content)->opcode - 1].nb_p)
				{
					//ft_printf("param %d : %s, ",i + 1, (((t_line*)g_lines->content)->param)[i]);
					i++;
				}
			}
			//ft_printf("\n");
		}
		g_lines = g_lines->next;
	}
	g_lines = keep;
	// free_g_line();
	ft_printf("champion créé\n");
	return (0);
}
