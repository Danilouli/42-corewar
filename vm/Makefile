# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 17:18:12 by fsabatie          #+#    #+#              #
#    Updated: 2018/05/10 16:41:30 by vlay             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re peace

GREEN = \033[0;32m
RESET = \033[0m

NAME = corewar
CC = gcc
INCLUDE_PATH = includes/
INCLUDE = op.h

SRC_PATH = ./src/
OBJ_PATH = ./build/
LIB_PATH = ../
INC_PATH = ./includes/ $(LIB_PATH)libft/includes/ $(LIB_PATH)glfw/include/

GCC_FLGS = -g -Werror -Wextra -Wall
GCC_LIBS = -lglfw3 -lncurses -framework AppKit -framework OpenGL -framework IOKit \
			-framework OpenCL -framework CoreVideo

SRC_NAME = 	champ.c misc.c vm.c operations.c process.c opt.c map.c env.c \
			render.c shaders.c args.c st_i.c ld_i.c forks.c operators.c \
			aff_jmp_live.c action.c ocp.c

OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_NAME = libft glfw/src

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LIB = $(addprefix -L$(LIB_PATH),$(LIB_NAME))

all: $(NAME)

$(NAME): lib $(OBJ)
	@$(CC) $(GCC_FLGS) $(LIB) -lft $(INC) $(OBJ) $(GCC_LIBS) -o $(NAME)
	@echo "$(GREEN)Compiled the binary.$(RESET)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(GCC_FLGS) $(INC) -o $@ -c $<

lib:
	@make -C $(LIB_PATH)libft
	@echo "$(GREEN)Compiled libft.$(RESET)"

clean:
	@make clean -C ../libft
	@rm -rf $(OBJ_PATH)

fclean: clean
	@make fclean -C ../libft
	@rm -rf $(NAME)

re: fclean all

test: lib
	@gcc test.c $(LIB) -o main
	@./main

peace:
	@clear;
	@echo "$(GREEN)"
	@echo "                                                 ."
	@echo "                                                 :\`"
	@echo "                                                 ++"
	@echo "                                                .ss:"
	@echo "                                                +yys."
	@echo "                                               -yyys/                   \`"
	@echo "                            \`                  oyyyso                 .:"
	@echo "                             -/-\`             .syyyys.             \`:o/"
	@echo "                              \`oyo:\`          :yyyyys:           :oyyo"
	@echo "                               .syyso-\`       +yyyyys/        -+syyyo\`"
	@echo "                                \`oyyyys/\`    \`syyyyss:     ./syyyyyo\`"
	@echo "                                 \`oyyyyys:   .yyyyyss:   \`/yyyyyyso\`"
	@echo "                                  \`oyyyyyyo. .yyyyyss-  -yyyyyyss+"
	@echo "                                   \`+yyyyyyy- +yyyyss\`\`+yyyyysss/\`"
	@echo "                                     -syyyyyy-.syyys/.oyyyyyss+."
	@echo "                                       -oyyyys\`-yyyo.syyyyss/."
	@echo "                          \`.-/+//:/::-.\` \`-+yyo :yo.oyyso:-\`.-:/++ooso/:.\`"
	@echo "                              ./oyyyyyyyso/-\`.// o.++-..:+osyyyyyys+-"
	@echo "                                 \`./+ossyysss+::://-:ossyyyyyyso/."
	@echo "                                         \`./+os:\`.:so++/:-.-\`\`"
	@echo "                                      \`-oyys/-\` \`. \`:oyhhy+-"
	@echo "                                    \`:+/:.\`     .\`     ./ooys:\`"
	@echo "                                   \`-           .           \`./:"
	@echo "                                                -               \`"
	@echo "                                                -"
	@echo "                                                -"
