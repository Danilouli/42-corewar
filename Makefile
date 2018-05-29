# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 17:18:12 by fsabatie          #+#    #+#              #
#    Updated: 2018/05/29 15:33:17 by acouturi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re peace asm vm dasm

# Defining colors

RED		= \033[1;31m
GREEN	= \033[0;32m
ORANGE	= \033[0;33m
BLUE	= \033[1;36m
YELLOW	= \033[1;33m
PURPLE	= \033[1;35m
RESET	= \033[0m

_RED	= "\033[0;31m"
_NONE	= "\033[0m"
_SCIENCETXT = "\033[38;05;172m"

# Defining paths

LIB_PATH = libft
DASM_PATH = dasm
ASM_PATH = asm
VM_PATH = vm

# Defining rules

all: science lib dasm asm vm

lib:
	@make -C $(LIB_PATH)

dasm:
	@make -s -C $(DASM_PATH)

asm:
	@make -s -C $(ASM_PATH)

vm:
	@make -s -C $(VM_PATH)

clean:
	@make clean -C $(DASM_PATH)
	@make clean -C $(LIB_PATH)
	@make clean -C $(ASM_PATH)
	@make clean -C $(VM_PATH)

fclean:
	@make fclean -C $(DASM_PATH)
	@make fclean -C $(LIB_PATH)
	@make fclean -C $(ASM_PATH)
	@make fclean -C $(VM_PATH)

re: fclean all

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
	@sleep 0.1
	@clear
	@echo $(_SCIENCETXT)" \
			.,-:;//;:=,\n \
           :H@@@MM@M#H/.,+%;,\n \
           +M@@M@MM%=,-%HMMM@X/,\n \
            8M@@MH+-,;XMMMM@MMMM@+-\n \
            XM@X;. -+XXXXXHHH@M@M#@/.\n \
           ,@%=\n \
           .,\n\n\n\n\n\n\n\n\n\n\n\n\n"$(_NONE)
	@sleep 0.1
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
	@sleep 0.1
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
	@sleep 0.1
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
	@sleep 0.1
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
	@sleep 0.1
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
	@sleep 0.1
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
