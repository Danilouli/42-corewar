/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 11:36:09 by acouturi          #+#    #+#             */
/*   Updated: 2018/05/29 16:29:12 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DASM_H
# define DASM_H

# include "../../libft/includes/libft.h"
# include "op.h"
# define T_ALL T_REG | T_IND | T_DIR

typedef struct	s_error
{
	int			nberror;
	char		lastmsgerror[512];
}				t_error;

void			dasm_code(unsigned char *prog, int fd, uintmax_t lenrest);

#endif
