/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 17:56:08 by dsaadia           #+#    #+#             */
/*   Updated: 2018/05/01 16:05:44 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

t_corewar init_g_corewar(void) {
	t_corewar ret;

	ret.nb_lines = 0;
	ret.code_len = 0;
	ret.last_label = 0;
	return (ret);
}

void init_g_seps(void) {
	g_seps[0] = ' ';
	g_seps[1] = '\t';
	g_seps[2] = SEPARATOR_CHAR;
}

t_op		*init_g_op_tab(void)
{
	static t_op op_tab[17] = {
		{"live", 1, {T_DIR}, 1, 10, "", 0, 0},
		{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "", 1, 0},
		{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "", 1, 0},
		{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "", 1, 0},
		{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "", 1, 0},
		{"and", 3, {T_ALL, T_ALL, T_REG}, 6, 6, "", 1, 0},
		{"or", 3, {T_ALL, T_ALL, T_REG}, 7, 6, "", 1, 0},
		{"xor", 3, {T_ALL, T_ALL, T_REG}, 8, 6, "", 1, 0},
		{"zjmp", 1, {T_DIR}, 9, 20, "", 0, 1},
		{"ldi", 3, {T_ALL, T_DIR | T_REG, T_REG}, 10, 25, "", 1, 1},
		{"sti", 3, {T_REG, T_ALL, T_DIR | T_REG}, 11, 25, "", 1, 1},
		{"fork", 1, {T_DIR}, 12, 800, "", 0, 1},
		{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "", 1, 0},
		{"lldi", 3, {T_ALL, T_DIR | T_REG, T_REG}, 14, 50, "", 1, 1},
		{"lfork", 1, {T_DIR}, 15, 1000, "", 0, 1},
		{"aff", 1, {T_REG}, 16, 2, "", 1, 0},
		{0, 0, {0}, 0, 0, 0, 0, 0}
	};

	return (op_tab);
}

t_error	*init_g_d_errors(void)
{
	static t_error *init = NULL;

	if (!(init = (t_error*)malloc(sizeof(t_error))))
		return (0);
	init->lastmsgerror = 0;
	init->nberror = 0;
	init->nb_lines = 0;
	init->nb_char = 0;
	return (init);
}

t_list	*alloc_label(char *labelstr, char **spl)
{
	t_label *la;
	t_list *nw;

	if (!(la = (t_label*)malloc(sizeof(t_label))) && ft_memdelbool((void**)&la))
		return (super_herror("malloc error\n", 0));
	if (!(nw = (t_list*)malloc(sizeof(t_list))) && ft_memdelbool((void**)&nw))
		return (super_herror("malloc error\n", 0));
	la->value = labelstr;
	//ft_printf("APRES %p--%s\n",la->value,la->value);
	la->real_label = 0;
	la->addr = 0;
	la->spl = spl;
	nw->next = NULL;
	nw->content = la;
	nw->content_size = sizeof(t_label);
	return (nw);
}
