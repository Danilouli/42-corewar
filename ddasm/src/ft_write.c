/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 21:11:34 by acouturi          #+#    #+#             */
/*   Updated: 2018/04/05 21:45:36 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/dasm.h"

static unsigned char	decoupe_type(unsigned char type, int num)
{
	if (num == 1)
		type = (type / 64) % 4;
	else if (num == 2)
		type = (type / 16) % 4;
	else if (num == 3)
		type = (type / 4) % 4;
	else if (num == 4)
		type = type % 4;
	else
		type = 0;
	return (type);
}

static int				write_type(char ty, unsigned char *prog, int fd, t_op t)
{
	int lu;

	if (ty == REG_CODE && (lu = 1))
		ft_dprintf(fd, "r%u", prog[0]);
	else if (ty == DIR_CODE && t.need_c == 0 && (lu = 4))
		ft_dprintf(fd, "%c%u", DIRECT_CHAR, prog[0] * 256 * 256 * 256 +
			prog[1] * 256 * 256 + prog[2] * 256 + prog[3]);
	else if (ty == DIR_CODE && (lu = 2))
		ft_dprintf(fd, "%c%u", DIRECT_CHAR, prog[0] * 256 + prog[1]);
	else if (ty == IND_CODE && (lu = 2))
		ft_dprintf(fd, "%u", prog[0] * 256 + prog[1]);
	else
		lu = 0;
	return (lu);
	t.nb_p--;
}

static int				ft_put_line(unsigned char *prog, int fd, t_op this)
{
	int lu;
	int j;

	j = 1;
	lu = 1 + this.mod_c;
	if (this.mod_c == 1)
	{
		lu += write_type(decoupe_type(prog[1], j++), &prog[lu], fd, this);
		while (--this.nb_p)
		{
			ft_dprintf(fd, "%c ", SEPARATOR_CHAR);
			lu += write_type(decoupe_type(prog[1], j++), &prog[lu], fd, this);
		}
	}
	else
		lu += write_type(this.param[0], &prog[lu], fd, this);
	return (lu);
}

static t_op				*crea_op_tab(void)
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

void					dasm_code(unsigned char *prog, int fd, uintmax_t len)
{
	int			j;
	int			lu;
	t_op		*op_tab;

	op_tab = crea_op_tab();
	j = 0;
	while (op_tab[j].name && prog[0] != op_tab[j].code)
		j++;
	if (op_tab[j].name)
	{
		ft_dprintf(fd, "\t\t%-10s", op_tab[j].name);
		lu = ft_put_line(prog, fd, op_tab[prog[0] - 1]);
		ft_dprintf(fd, "\n");
	}
	else
		return ;
	if (len - lu > 0)
		dasm_code(&prog[lu], fd, len - lu);
}
