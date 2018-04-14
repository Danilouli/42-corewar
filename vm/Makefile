# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 17:18:12 by fsabatie          #+#    #+#              #
#    Updated: 2018/04/14 21:10:36 by vlay             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re peace

# Defining colors

RED = \033[1;31m
GREEN = \033[0;32m
ORANGE = \033[0;33m
BLUE = \033[1;36m
YELLOW = \033[1;33m
PURPLE = \033[1;35m
RESET = \033[0m

# Defining variables

NAME = corewar

INCLUDE_PATH = includes/
INCLUDE = op.h


LIB_NAME = libft.a
LIB_PATH = ../libft

SRC_FILE = op.c \
			vm.c \
			opt.c \
			champ.c \
			map.c

SRC_PATH = srcs/
OBJ_PATH = build/

LIB = $(addprefix $(LIB_PATH)/,$(LIB_NAME))

SRC = $(SRC_FILE:%.c=$(SRC_PATH)%.c)

INCL = $(INCLUDE:%.h=$(INCLUDE_PATH)%.h)

OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

# Compilation flags

CC = gcc
CPPFLAGS = -Wall -Wextra -Werror

# Defining rules

all: $(NAME)

$(NAME): lib $(OBJ) $(INCL)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -I$(INCLUDE_PATH) -L$(LIB_PATH) -lft

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(LIBFT_PATH)$(LIBFT_NAME)
	@mkdir -p $(OBJ_PATH)
	$(CC) -o $@ -c $< -I$(INCLUDE_PATH) $(CFLAGS)

lib:
	@make -C $(LIB_PATH)
	@echo "$(GREEN)Successfully compiled libft.$(RESET)"

clean:
	@make clean -C $(LIB_PATH)
	@rm -rf $(OBJ_PATH)

fclean: clean
	@make fclean -C $(LIB_PATH)
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
