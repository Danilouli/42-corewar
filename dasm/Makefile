# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/05 13:06:28 by acouturi          #+#    #+#              #
#    Updated: 2018/05/12 19:14:38 by acouturi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_DASM = dasm

LIBFT_DIR = ../libft/
LIBFT_NAME = libft.a
LIBFT = $(addprefix $(LIBFT_DIR),$(LIBFT_NAME))

SRC_DASM_DIR = ./src/
SRC_DASM_NAME = dasm.c ft_write.c
SRC_DASM = $(addprefix $(SRC_DASM_DIR),$(SRC_DASM_NAME))

OBJ_DIR = ./obj/

OBJ_DASM_NAME = $(SRC_DASM_NAME:.c=.o)
OBJ_DASM = $(addprefix $(OBJ_DIR),$(OBJ_DASM_NAME))

INCL = -I.

CFLAGS = -Werror -Wall -Wextra

# Colors
_BLACK	= "\033[0;30m"
_RED	= "\033[0;31m"
_GREEN	= "\033[0;32m"
_YELLOW	= "\033[1;33m"
_BLUE	= "\033[0;34m"
_PURPLE	= "\033[0;35m"
_CYAN	= "\033[0;36m"
_GREY	= "\033[0;37m"
_NONE	= "\033[0m"
_SCIENCEBIATCH = "\033[38;05;39m"
_SCIENCETXT = "\033[38;05;172m"

all : $(NAME_DASM)

colors :
	@echo $(_BLACK) _BLACK $(_RED) _RED $(_GREEN) _GREEN $(_YELLOW) _YELLOW $(_BLUE) _BLUE $(_PURPLE) _PURPLE $(_CYAN) _CYAN $(_GREY) _GREY $(_NONE) _NONE

$(NAME_DASM) : $(OBJ_DASM)
	@echo $(_YELLOW) "copy of libft.a" $(_NONE)
	@cp ../libft/libft.a .
	@echo $(_CYAN) "Created :	" $(_NONE) $(NAME_DASM)
	@gcc $(CFLAGS) -o $(NAME_DASM) $(SRC_DASM) $(LIBFT)
	@rm -rf $(LIBFT_NAME)

$(OBJ_DIR)%.o : $(SRC_DASM_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo $(_CYAN) "Compiling :	" $(_NONE) $^
	@gcc $(CFLAGS) -o $@ -c $<

clean:
	@echo $(_RED) "Remove :" $(OBJ_DIR)
	@/bin/rm -rf $(OBJ_DIR)
	@echo $(_RED) "Remove :" $(LIBFT_NAME)
	@/bin/rm -rf $(LIBFT_NAME)
	@echo $(_GREEN) "DONE" $(_NONE)

fclean: clean
	@echo $(_RED) "Remove :" $(NAME_DASM)
	@/bin/rm -f $(NAME_DASM)
	@echo $(_GREEN) "DONE" $(_NONE)

re: fclean all

exe: all clean

.PHONY: all clean fclean re exe science

science:
	@clear
	@echo $(_SCIENCETXT)" \
			.,-:;//;:=,\n \
           :H@@@MM@M#H/.\n \
           +M@@M@MM%=,\n \
            8M@@MH+-,\n \
            XM@X;.\n \
           ,@%=\n \
           .,\n\n\n\n\n\n\n\n\n\n\n\n\n"$(_NONE)
	@sleep 0.5
	@clear
	@echo $(_SCIENCETXT)" \
			.,-:;//;:=,\n \
           :H@@@MM@M#H/.,+%;,\n \
           +M@@M@MM%=,-%HMMM@X/,\n \
            8M@@MH+-,;XMMMM@MMMM@+-\n \
            XM@X;. -+XXXXXHHH@M@M#@/.\n \
           ,@%=\n \
           .,\n\n\n\n\n\n\n\n\n\n\n\n\n"$(_NONE)
	@sleep 0.5
	@clear
	@echo $(_SCIENCETXT)" \
			.,-:;//;:=,\n \
           :H@@@MM@M#H/.,+%;,\n \
           +M@@M@MM%=,-%HMMM@X/,\n \
            8M@@MH+-,;XMMMM@MMMM@+-\n \
            XM@X;. -+XXXXXHHH@M@M#@/.\n \
           ,@%=            .---=-=:=,.\n \
           .,              -%HX88%%%+;\n \
                            .;@MMMM@MM:\n \
                              .+MM@@@M8\n \
                              . -X#@@@@-\n \
                                  ;@M@M=\n \
                                   .%#8.\n \
                                     -;\n\n\n\n\n\n\n"$(_NONE)
	@sleep 0.5
	@clear
	@echo $(_SCIENCETXT)" \
			.,-:;//;:=,\n \
           :H@@@MM@M#H/.,+%;,\n \
           +M@@M@MM%=,-%HMMM@X/,\n \
            8M@@MH+-,;XMMMM@MMMM@+-\n \
            XM@X;. -+XXXXXHHH@M@M#@/.\n \
           ,@%=            .---=-=:=,.\n \
           .,              -%HX88%%%+;\n \
                            .;@MMMM@MM:\n \
                              .+MM@@@M8\n \
                              . -X#@@@@-\n \
                              /H- ;@M@M=\n \
                              %MM+..%#8.\n \
                              XM@MH; -;\n \
                             .H@@@@MX,\n \
                             ,@@@@@MX,\n \
                             -M@@MM%.\n \
                             /MMMX=\n \
                             %M%=\n \
                             -,\n"$(_NONE)
	@sleep 0.5
	@clear
	@echo $(_SCIENCETXT)" \
			.,-:;//;:=,\n \
           :H@@@MM@M#H/.,+%;,\n \
           +M@@M@MM%=,-%HMMM@X/,\n \
            8M@@MH+-,;XMMMM@MMMM@+-\n \
            XM@X;. -+XXXXXHHH@M@M#@/.\n \
           ,@%=            .---=-=:=,.\n \
           .,              -%HX88%%%+;\n \
                            .;@MMMM@MM:\n \
                              .+MM@@@M8\n \
                              . -X#@@@@-\n \
                              /H- ;@M@M=\n \
                              %MM+..%#8.\n \
                              XM@MH; -;\n \
                           , .H@@@@MX,\n \
                         -%H.,@@@@@MX,\n \
                      .:8MMX -M@@MM%.\n \
                   ,-+HMM@M+ /MMMX=\n \
                 .=8@MM@@@M; %M%=\n \
               ,/H#MMMMMMM@- -,\n \
               =++%%%%+/:-."$(_NONE)
	@sleep 0.5
	@clear
	@echo $(_SCIENCETXT)" \
			.,-:;//;:=,\n \
           :H@@@MM@M#H/.,+%;,\n \
           +M@@M@MM%=,-%HMMM@X/,\n \
            8M@@MH+-,;XMMMM@MMMM@+-\n \
            XM@X;. -+XXXXXHHH@M@M#@/.\n \
           ,@%=            .---=-=:=,.\n \
           .,              -%HX88%%%+;\n \
                            .;@MMMM@MM:\n \
                              .+MM@@@M8\n \
                              . -X#@@@@-\n \
                              /H- ;@M@M=\n \
                              %MM+..%#8.\n \
                              XM@MH; -;\n \
                           , .H@@@@MX,\n \
   .=--------.           -%H.,@@@@@MX,\n \
   .%MM@@@HHHXX888%+- .:8MMX -M@@MM%.\n \
     =XMMM@MM@MM#H;,-+HMM@M+ /MMMX=\n \
       =%@M@M#@8-.=8@MM@@@M; %M%=\n \
         ,:+8+-,/H#MMMMMMM@- -,\n \
               =++%%%%+/:-."$(_NONE)
	@sleep 0.5
	@clear
	@echo $(_SCIENCETXT)" \
			.,-:;//;:=,\n \
           :H@@@MM@M#H/.,+%;,\n \
           +M@@M@MM%=,-%HMMM@X/,\n \
            8M@@MH+-,;XMMMM@MMMM@+-\n \
            XM@X;. -+XXXXXHHH@M@M#@/.\n \
           ,@%=            .---=-=:=,.\n \
           .,              -%HX88%%%+;\n \
 =-                         .;@MMMM@MM:\n \
 X@/                          .+MM@@@M8\n \
,@M@H:                        . -X#@@@@-\n \
,@@@MMX,                      /H- ;@M@M=\n \
.H@@@@M@+,                    %MM+..%#8.\n \
 /MMMM@MMH/.                  XM@MH; -;\n \
  /%+%8XHH@8=              , .H@@@@MX,\n \
   .=--------.           -%H.,@@@@@MX,\n \
   .%MM@@@HHHXX888%+- .:8MMX -M@@MM%.\n \
     =XMMM@MM@MM#H;,-+HMM@M+ /MMMX=\n \
       =%@M@M#@8-.=8@MM@@@M; %M%=\n \
         ,:+8+-,/H#MMMMMMM@- -,\n \
               =++%%%%+/:-."$(_NONE)
	@sleep 0.5
	@clear
	@echo $(_SCIENCETXT)" \
			.,-:;//;:=,\n \
         . :H@@@MM@M#H/.,+%;,\n \
      ,/X+ +M@@M@MM%=,-%HMMM@X/,\n \
     -+@MM; 8M@@MH+-,;XMMMM@MMMM@+-\n \
    ;@M@@M- XM@X;. -+XXXXXHHH@M@M#@/.\n \
  ,%MM@@MH ,@%=            .---=-=:=,.\n \
  -@#@@@MX .,              -%HX88%%%+;\n \
 =-./@M@M8                  .;@MMMM@MM:\n \
 X@/ -8MM/                    .+MM@@@M8\n \
,@M@H: :@:                    . -X#@@@@-\n \
,@@@MMX, .                    /H- ;@M@M=\n \
.H@@@@M@+,                    %MM+..%#8.\n \
 /MMMM@MMH/.                  XM@MH; -;\n \
  /%+%8XHH@8=              , .H@@@@MX,\n \
   .=--------.           -%H.,@@@@@MX,\n \
   .%MM@@@HHHXX888%+- .:8MMX -M@@MM%.\n \
     =XMMM@MM@MM#H;,-+HMM@M+ /MMMX=\n \
       =%@M@M#@8-.=8@MM@@@M; %M%=\n \
         ,:+8+-,/H#MMMMMMM@- -,\n \
               =++%%%%+/:-.\n\n "$(_NONE)
	@sleep 0.2
	@echo $(_SCIENCETXT)"          This was a triumph."
	@sleep 0.2
	@echo $(_SCIENCETXT)"         I'm making a note here:"
	@sleep 0.2
	@echo $(_SCIENCETXT)"              "$(_RED)"HUGE SUCCESS."$(_SCIENCETXT)
	@sleep 0.2
	@echo $(_SCIENCETXT)"         It's hard to overstate"
	@sleep 0.2
	@echo $(_SCIENCETXT)"            my satisfaction."
	@sleep 0.2
	@echo $(_SCIENCETXT)"              Enter a name"
	@sleep 0.2
	@echo $(_SCIENCETXT)"           We do what we must"
	@sleep 0.2
	@echo $(_SCIENCETXT)"             because we can."
	@sleep 0.2
	@echo $(_SCIENCETXT)"       For the good of all of us."
	@sleep 0.2
	@echo $(_SCIENCETXT)"      Except the ones who are dead."$(_NONE)
