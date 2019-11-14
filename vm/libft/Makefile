# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbrizon <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/15 17:09:42 by tbrizon           #+#    #+#              #
#    Updated: 2019/07/02 12:43:07 by jjaegle          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC_PATH = ./srcs/

SC = 	flags.c \
		dispatcher.c \
		char.c \
		hexa.c \
		int.c \
		ft_initialise.c \
		ft_nbcarint.c \
		octet.c \
		ptr.c \
		ft_is.c \
		str.c \
		unsign.c \
		float.c \
		ft_is_in.c \
		fn_float.c \
		fn_exp.c \
		ft_parsing.c \
		addition.c \
		ft_strf.c \
		mask.c \
		fn_float2.c \
		ft_parsing_all.c \
		fn_fill.c \
		fn_buff.c \
		exp.c \
		print.c \
		write.c \
		ft_printf.c \
		binary.c \
		star.c \
		jumpin.c \

LIBFT = ./lib

LIBFT_A = ./lib/libft.a

D_SRCS = ./srcs

D_OBJ = ./temporary

HEADER = ./includes

CC = gcc $(CFLAGS)

CFLAGS = -Wall -Wextra -Werror

SRCS = $(addprefix $(D_SRCS)/,$(SC))

OBJ = $(addprefix $(D_OBJ)/,$(SC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[34mCreation of libft.a ...\n\033[0m"
	@make -C $(LIBFT)
	@echo "\033[34mCreation of $(NAME) ...\n\033[0m"
	@cp $(LIBFT_A) ./$(NAME)
	@ar -rc $(NAME) $(OBJ) $(LIBFT_A)
	@ranlib $(NAME)
	@echo "\033[32m[OK]  $(NAME) created\n\033[0m"

$(D_OBJ)/%.o: $(D_SRCS)/%.c
	@mkdir -p temporary
	@$(CC) $(FLAGS) -o $@ -c $<

clean:
	@make clean -C ./lib/
	@echo
	@echo "\033[34mRemoval of .o files of printf ...\033[0m"
	@rm -f $(OBJ)
	@rm -rf $(D_OBJ)
	@echo "\033[31mFiles .o are deleted\n\033[0m"

fclean:
	@make fclean -C ./lib/
	@echo "\033[34mRemoval of .o files of printf ...\033[0m"
	@rm -f $(OBJ)
	@rm -rf $(D_OBJ)
	@echo "\033[31mFiles .o are deleted\n\033[0m"
	@echo "\033[33mRemoval of $(NAME)...\033[0m"
	@rm -f $(NAME)
	@echo "\033[31m$(NAME) deleted\n\033[0m"

re: fclean all

norme:
	norminette ./lib/
	@echo
	norminette ./$(HEADER)/
	@echo
	norminette ./$(D_SRCS)/


.PHONY: all, clean, fclean, re
