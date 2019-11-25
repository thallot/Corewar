# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbrizon <tbrizon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/15 17:09:42 by tbrizon           #+#    #+#              #
#    Updated: 2019/11/25 11:59:33 by jjaegle          ###   ########.fr        #
#    Updated: 2019/11/14 16:35:47 by jjaegle          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VM = corewar

ASM = assembler

SRC_PATH = ./srcs_vm/

SC_VM = vm.c \
	 fn_file.c \
	 fn_tab.c \
	 error.c \
	 process.c \
	 memory.c \
	 tools.c \
	 game.c \
	 play.c \
	 ld_st_live.c \
	 tools2.c \
	 tools3.c \
	 add_sub.c \
	 and_or.c \
	 xor_zjmp.c \
	 ldi_sti.c \
	 fork_lfork.c \
	 aff.c \
	 visu.c \
	 visu_print.c \
	 visu_param.c \

LIBFT = ./libft

LIBFT_A = ./libft/libftprintf.a

D_SRCSVM = ./srcs_vm

D_OBJ = ./temporary

HEADER = ./includes

CC = gcc $(CFLAGS)

CFLAGS = -Wall -Wextra -Werror -lncurses #-g -fsanitize=address

SRCS_VM = $(addprefix $(D_SRCSVM)/,$(SC_VM))

OBJ = $(addprefix $(D_OBJ)/,$(SC:.c=.o))

all: $(VM) $(ASM)

$(VM): $(LIBFT_A) $(SRCS_VM) ./includes/vm.h ./includes/op.h
	@$(CC) $(FLAGS) -o $(VM) -I $(HEADER) $(SRCS_VM) $(LIBFT_A)
	@echo "\033[32m[OK]  $(VM) created\n\033[0m"

$(LIBFT_A):
	@echo "\033[34mCreation of $(VM) ...\n\033[0m"
	@make -C $(LIBFT)

clean:
	@make clean -C ./libft/

fclean-lib:
	@make fclean -C ./libft/
	@echo "\033[33mRemoval of $(VM)...\033[0m"
	@rm -f $(VM)
	@echo "\033[31m$(VM) deleted\n\033[0m"

fclean:
	@echo "\033[33mRemoval of $(VM)...\033[0m"
	@rm -f $(VM)
	@echo "\033[31m$(VM) deleted\n\033[0m"
	@rm -rf .venv

re: fclean all

re-lib: fclean-lib all

norme:
	norminette ./libft/
	@echo
	norminette ./$(HEADER)/
	@echo
	norminette ./$(D_SRCS)/

.PHONY: all, clean, fclean, re
