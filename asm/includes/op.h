/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <zaz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2018/04/14 18:50:13 by dsaadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

#ifndef OP_H
# define OP_H

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4				//osef
#define MAX_PLAYERS				4				//osef
#define MEM_SIZE				(4*1024)		//osef
#define IDX_MOD					(MEM_SIZE / 8)	//osef
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)	//osef

#define COMMENT_CHAR			'#'				//osef
#define LABEL_CHAR				':'				//osef
#define DIRECT_CHAR				'%'				//done
#define SEPARATOR_CHAR			','				//done

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"			//osef
#define COMMENT_CMD_STRING		".comment"		//osef

#define REG_NUMBER				16				//osef

#define CYCLE_TO_DIE			1536			//osef
#define CYCLE_DELTA				50				//osef
#define NBR_LIVE				21				//osef
#define MAX_CHECKS				10				//osef

/*
**
*/

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		(128)				//done
# define COMMENT_LENGTH			(2048)				//done
# define COREWAR_EXEC_MAGIC		0xea83f3			//done

typedef struct		header_s
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}					header_t;

typedef struct		s_op
{
	char			*name; 			//  Nom de l'instruction
	char			nb_p; 			//  Nombre de parametres
	char			param[4]; 		//  Parametres
	char			code; 			//  Opcode
	unsigned short	cycles; 		//o  Nombre de cycles pour realiser l'instruction
	char			*des; 			//o  Description
	char			mod_c; 			//d  OCP
	char			need_c; 		//d  2 / 4 octets
}					t_op;

//		01 00 00 00 01			live	%1
//		02 90 00 00 00 01 02	ld		%1, r2
//		03 50 02 02				st		r2, r2
//		04 54 02 02 02			add		r2, r2, r2
//		05 54 02 02 02			sub		r2, r2, r2
//		06 54 02 02 02			and		r2, r2, r2
//		06 64 02 00 00 00 01 02	and		r2, %1, r2
//		06 74 02 00 01 02    	and		r2, 1, r2
//		07 54 02 02 02			or		r2, r2, r2
//		08 54 02 02 02			xor		r2, r2, r2
//		09 00 03				zjmp	%:c
//c:	0a a4 00 01 00 01 02	ldi		%1, %1, r2
//		0b 68 02 00 01 00 01	sti 	r2, %1, %1
//		0c 00 03				fork	%:b
//b:	0d 90 00 00 00 01 02	lld		%1, r2
//		0e a4 00 01 00 01 02	lldi	%1, %1, r2
//		10 40 02				aff		r2
//		0f 00 03        		lfork	%:a
//a:

//137 * 16 en header puis code
/*
// (4oct) 00ea83f3 magic....
// (128oct) name
// (4oct) 0000 fin nom  <<pas sur d la taille entre ces deux
// (4oct) taille prog   <<ligne mais sur de la taille total
// (2048oct) comment
// (4oct) 00000000 fin com
// 2,192
*/

#endif
