# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 17:18:12 by fsabatie          #+#    #+#              #
#    Updated: 2018/04/01 20:25:49 by dsaadia          ###   ########.fr        #
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

NAME = asm
LIB_NAME = libft.a
LIB_PATH = ../libft
ASM_SRCS = ..
BUILD_PATH = build

ASM_SRC_F =	main.c

OBJ_NAME = $(ASM_SRC_F:.c=.o)
OBJS = $(addprefix $(BUILD_PATH)/,$(OBJ_NAME))
SRCS = $(addprefix $(ASM_SRCS)/,$(ASM_SRC_F))
LIB = $(addprefix $(LIB_PATH)/,$(LIB_NAME))

# Compilation flags

CC = gcc
CPPFLAGS = -Wall -Wextra -Werror

# Defining rules

all: $(NAME)

lib:
	@make -C $(LIB_PATH)
	@echo "$(GREEN)Successfully compiled libft.$(RESET)"

$(NAME): lib
	@mkdir -p $(BUILD_PATH) && cd $(BUILD_PATH) && $(CC) $(CPPFLAGS) -c $(SRCS)
	@$(CC) $(CPPFLAGS) -o $(NAME) $(OBJS) $(LIB)
	@echo "$(GREEN)Successfully the asm binary.$(RESET)"

clean:
	@make clean -C $(LIB_PATH)
	@rm -rf $(BUILD_PATH)

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
