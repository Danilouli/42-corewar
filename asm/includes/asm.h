/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaadia <dsaadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 19:23:12 by dsaadia           #+#    #+#             */
/*   Updated: 2018/05/14 10:07:36 by danielsaadia     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../../libft/includes/libft.h"
# include "./op.h"

# define ISSPTB(c) (c == ' ' || c == '\t')
# define LASTC(str) str[ft_strlen(str) - 1]
# define LINEOP 	 g_op_tab[line->opcode - 1]
# define OPL(line)			g_op_tab[line->opcode - 1]
# define LINECONT(lst)  ((t_line*)lst->content)
# define LABCONT(lst)  ((t_label*)lst->content)
# define T_ALL T_REG | T_IND | T_DIR
# define NB_LINES				g_corewar.nb_lines
# define CODE_LEN				g_corewar.code_len
# define LAST_LABEL			g_corewar.last_label

typedef struct			s_line
{
	char				*label;
	int					opcode;
	int					len;
	int					len_tot;
	int					addr;
	int					nb_params;
	char				**param;
	char				*line;
}						t_line;

typedef struct			s_label
{
	char				*value;
	char				**spl;
	char				*real_label;
	int					addr;
}						t_label;

typedef struct			s_corewar
{
	int					nb_lines;
	int					code_len;
	char				*last_label;
}						t_corewar;

char					g_seps[3];

t_corewar				g_corewar;

t_list					*g_lines;

t_list					*g_labels;

t_op					*g_op_tab;

int						g_nberror;

int						read_code(char *l);
void					init_g_seps(void);
int						is_label(char *str);
int						is_op_name(char *str);
t_op					*init_g_op_tab(void);
int						fetch_opcode(char *op_name);
t_list					*alloc_line(char **spl, char *label, int nbp, char *l);
int						is_direct(char *str);
int						is_reg(char *str);
int						is_indirect(char *str);
int						what_is(char *str);
int						check_params(t_line *line);
char					*destroy(char **del);
char					*have_truc(int fd, char *truc);
int						have_header(int fd);
void					calc_len(t_line *line);
char					*reinit_direct(char **dir, int addrnb, int addrline);
char					*reinit_indirect(char **ind, int addrnb, int addrline);
int						is_real_code(void);
int						is_real_label(char *str);
char					*is_label_ind(char *ind);
char					*is_label_dir(char *dir);
t_corewar				init_g_corewar(void);
int						init_len_code(void);
int						create_open_cor(char *spath, int fds);
void					write_magic(int fdc, int *magic);
void					write_name(int fdc, char *name);
void					write_len_code(int fdc, int *len_code);
void					write_comment(int fdc, char *comment);
void					write_line(int fdc, t_line *line);
void					endian_swap(unsigned int *ptr);
int						create_ocp(t_line *line);
void					short_endian_swap(unsigned short *ptr);
void					free_all(void);
void					*super_herror(char *msg, int char_ind);
t_list					*alloc_label(char *label, char **spl);
void					redefine_labels(char *final_label);
int						is_relabel(char *str);
char					*fetch_final_label(char *label);
int 					gce(char *err_word, char *l);

#endif
