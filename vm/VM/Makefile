# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbrizon <tbrizon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/15 17:09:42 by tbrizon           #+#    #+#              #
#    Updated: 2019/11/15 16:00:16 by edillenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

SRC_PATH = ./srcs/

SC = vm.c \
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
	 add_sub.c \
	 and_or.c \
	 xor_zjmp.c \
	 ldi_sti.c \
	 sti.c

LIBFT = ../libft

LIBFT_A = ../libft/libftprintf.a

D_SRCS = ./srcs

D_OBJ = ./temporary

HEADER = ../includes

CC = gcc $(CFLAGS)

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

SRCS = $(addprefix $(D_SRCS)/,$(SC))

OBJ = $(addprefix $(D_OBJ)/,$(SC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT_A) $(SRCS) ../includes/vm.h ../includes/op.h
	@$(CC) $(FLAGS) -o $(NAME) -I $(HEADER) $(SRCS) $(LIBFT_A)
	@echo "\033[32m[OK]  $(NAME) created\n\033[0m"

$(LIBFT_A):
	@echo "\033[34mCreation of $(NAME) ...\n\033[0m"
	@make -C $(LIBFT)

clean:
	@make clean -C ../libft/

fclean-lib:
	@make fclean -C ../libft/
	@echo "\033[33mRemoval of $(NAME)...\033[0m"
	@rm -f $(NAME)
	@echo "\033[31m$(NAME) deleted\n\033[0m"

fclean:
	@echo "\033[33mRemoval of $(NAME)...\033[0m"
	@rm -f $(NAME)
	@echo "\033[31m$(NAME) deleted\n\033[0m"
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
