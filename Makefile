# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thallot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/27 16:42:47 by edillenb          #+#    #+#              #
#    Updated: 2019/11/29 15:50:20 by jjaegle          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM = asm
VM = corewar

CFLAGS_ASM = -Wall -Werror -Wextra
CFLAGS_VM = -Wall -Werror -Wextra -lncurses
CC = gcc
LIBFT_ASM = lib/libft/libft.a
LIBFT_VM = libft/libftprintf.a
LIBFTPRINTF = lib/printf/libftprintf.a

SRCDIR_ASM = src
OBJDIR_ASM = obj_asm

SC_ASM = $(addsuffix .c, main \
	get_asm \
	garbage_collector \
	 parsing byte_ope \
	file_parser \
	gc_functions \
	ft_tab_one \
	ft_tab_two \
	ft_tab_three \
	ft_tab_four \
	writer \
	utils \
	util_parsing)

SRCS_ASM = $(addprefix $(SRCDIR_ASM)/, $(SC_ASM))
OBJS_ASM = $(addprefix $(OBJDIR_ASM)/, $(SC_ASM:.c=.o))
INCLS_ASM = $(addprefix ./include/, $(addsuffix .h, asm))

SRCDIR_VM = srcs
OBJDIR_VM = obj_vm

SC_VM = $(addsuffix .c, vm \
	 fn_file \
	 fn_tab \
	 error \
	 process \
	 memory \
	 tools \
	 game \
	 play \
	 ld_st_live \
	 tools2 \
	 tools3 \
	 add_sub \
	 and_or \
	 xor_zjmp \
	 ldi_sti \
	 fork_lfork \
	 aff \
	 visu \
	 visu_print \
	 visu_print_two \
	 visu_print_three \
	 visu_param)

SRCS_VM = $(addprefix $(SRCDIR_VM)/, $(SC_VM))
OBJS_VM = $(addprefix $(OBJDIR_VM)/, $(SC_VM:.c=.o))
INCLS_VM = $(addprefix ./includes/, $(addsuffix .h, op vm))
HEADER= ./includes

GREEN = \033[01;32m
BLUE = \033[01;34m
_BLUE=$ \x1b[36m
GREY=$ \x1b[33m
RED = \033[01;31m
YELLOW = \033[01;33m
MAGENTA = \033[35m
BLACK = \033[30m
NOCOLOR = \033[0m
WHITE=$ \x1b[37m
BOLD= \033[1m

all: $(ASM) $(VM)

$(ASM): $(LIBFTPRINTF) $(LIBFT_ASM) $(OBJS_ASM)
	@echo "$(BOLD)$(GREY)~~~~~~~~~~~~ Generation ~~~~~~~~~~~~"
	@$(CC) $(CFLAGS_ASM) $(LIBFTPRINTF) $(LIBFT_ASM) $(OBJS_ASM) -o $(ASM)
	@echo "$(GREEN)[OK] $(GREY)Tous les objets de $(WHITE)$(ASM) $(GREY)sont generes !\r"
	@echo "$(GREEN)[OK] $(GREY)Compilation de $(WHITE)$(ASM)\n"

$(OBJS_ASM) : $(INCLS_ASM)

$(VM): $(SRCS_VM) $(OBJS_VM)
	@echo "$(BOLD)$(GREY)~~~~~~~~~~~~ Generation ~~~~~~~~~~~~"
	@$(CC) $(CFLAGS_VM) $(LIBFT_VM) $(OBJS_VM) -o $(VM)
	@echo "$(GREEN)[OK] $(GREY)Tous les objets de $(WHITE)$(VM) $(GREY)sont generes !\r"
	@echo "$(GREEN)[OK] $(GREY)Compilation de $(WHITE)$(VM)\n"

$(OBJS_VM) : $(INCLS_VM)

$(OBJDIR_VM)/%.o: $(SRCDIR_VM)/%.c
		@mkdir -p $(OBJDIR_VM)
	  @$(CC) -I $(HEADER) $(CFLAGS) -c -o $@ $<

$(OBJDIR_ASM)/%.o: $(SRCDIR_ASM)/%.c
		@mkdir -p $(OBJDIR_ASM)
	  @$(CC) $(CFLAGS) -c -o $@ $<

lib: menu_lib $(LIBFTPRINTF) $(LIBFT)

menu_lib: FORCE
	@echo "$(BOLD)$(_BLUE)~~~~~~~~~~~~ Library ~~~~~~~~~~~~~~~"

$(LIBFTPRINTF): FORCE
	@make -C lib/printf/
	@echo "$(NOCOLOR)"

$(LIBFT_ASM): FORCE
	@make -C lib/libft/
	@echo "$(NOCOLOR)"

FORCE:

clean:
	@echo "$(BOLD)$(RED)~~~~~~~~~~~~ Delete ~~~~~~~~~~~~~~~~"
	@echo "$(GREEN)[OK]$(RED) Supression des objets de $(WHITE)$(ASM)"
	@echo "$(GREEN)[OK]$(RED) Supression des objets de $(WHITE)$(VM)"
	@echo "$(GREEN)[OK]$(RED) Supression des objets de $(WHITE)libft"
	@echo "$(GREEN)[OK]$(RED) Supression des objets de $(WHITE)libftprintf"
	@make clean -C lib/libft
	@make clean -C lib/printf
	@rm -rf $(OBJDIR_ASM)
	@rm -rf $(OBJDIR_VM)

fclean: clean
	@echo "$(GREEN)[OK]$(RED) Supression de $(WHITE)$(VM)"
	@echo "$(GREEN)[OK]$(RED) Supression de $(WHITE)$(ASM)"
	@make fclean -C lib/libft
	@make fclean -C lib/printf
	@rm -f $(ASM)
	@rm -rf $(VM)

re: fclean all

.PHONY: all clean fclean re lib menu_lib
