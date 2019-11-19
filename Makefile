# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thallot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/27 16:42:47 by edillenb          #+#    #+#              #
#    Updated: 2019/11/13 14:11:20 by edillenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = assembler

CFLAGS = -Wall -Werror -Wextra -lncurses
CC = gcc
LIBFT = lib/libft/libft.a
LIBFTPRINTF = lib/printf/libftprintf.a

OBJDIR = obj
SRCDIR = src

SC = $(addsuffix .c, main get_asm garbage_collector parsing byte_ope \
	file_parser gc_functions ft_tab_one ft_tab_two ft_tab_three ft_tab_four \
	writer utils util_parsing)

SRCS = $(addprefix $(SRCDIR)/, $(SC))
OBJS = $(addprefix $(OBJDIR)/, $(SC:.c=.o))
INCLS = $(addprefix ./include/, $(addsuffix .h, asm))

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

all: $(NAME)

$(NAME): $(LIBFTPRINTF) $(LIBFT) $(OBJS) $(INCLS)
	@echo "$(BOLD)$(GREY)~~~~~~~~~~~~ Generation ~~~~~~~~~~~~"
	@$(CC) $(CFLAGS) $(LIBFTPRINTF) $(LIBFT) $(OBJS) -o $(NAME)
	@echo "$(GREEN)[OK] $(GREY)Tous les objets de $(WHITE)$(NAME) $(GREY)sont generes !\r"
	@echo "$(GREEN)[OK] $(GREY)Compilation de $(WHITE)$(NAME)\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p obj
	@$(CC) $(CFLAGS) -c -o $@ $< && printf "$(GREEN)[OK] $(GREY)Generation de $(WHITE)%-50s\r" "$@" || \
		(echo "$(_RED)[ERREUR]$(_GRAY) Une est erreur est survenue sur $(WHITE)$<$(RED), $(WHITE)$(NAME)$(RED) non compilé(e)\n" && exit 1)

lib: menu_lib $(LIBFTPRINTF) $(LIBFT)

menu_lib: FORCE
	@echo "$(BOLD)$(_BLUE)~~~~~~~~~~~~ Library ~~~~~~~~~~~~~~~"

$(LIBFTPRINTF): FORCE
	@make -C lib/printf/
	@echo "$(NOCOLOR)"

$(LIBFT): FORCE
	@make -C lib/libft/
	@echo "$(NOCOLOR)"

FORCE:

clean:
	@echo "$(BOLD)$(RED)~~~~~~~~~~~~ Delete ~~~~~~~~~~~~~~~~"
	@echo "$(GREEN)[OK]$(RED) Supression des objets de $(WHITE)$(NAME)"
	@echo "$(GREEN)[OK]$(RED) Supression des objets de $(WHITE)libft.a"
	@echo "$(GREEN)[OK]$(RED) Supression des objets de $(WHITE)libftprintf.a"
	@make clean -C lib/libft
	@make clean -C lib/printf
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "$(GREEN)[OK]$(RED) Supression de $(WHITE)$(NAME)"
	@make fclean -C lib/libft
	@make fclean -C lib/printf
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re lib
