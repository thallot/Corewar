# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/06 16:55:56 by jjaegle           #+#    #+#              #
#    Updated: 2019/11/09 17:35:13 by jjaegle          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=./libft.a

CC= gcc

FLAGS = -Wall -Wextra -Werror

SRCS=ft_memalloc.c   ft_putendl.c    ft_strdel.c     ft_strncat.c    ft_strsub.c \
		ft_atoi.c       ft_memccpy.c    ft_putendl_fd.c ft_strdup.c     ft_strncmp.c    ft_strtrim.c \
		ft_bzero.c      ft_memchr.c     ft_putnbr.c     ft_strequ.c     ft_strncpy.c    ft_tolower.c \
		ft_isalnum.c    ft_memcmp.c     ft_putstr.c     ft_striter.c    ft_strnequ.c    ft_toupper.c \
		ft_isalpha.c    ft_memcpy.c     ft_putstr_fd.c  ft_striteri.c   ft_strnew.c   	ft_putnbr_fd.c \
		ft_isascii.c    ft_memdel.c     ft_strcat.c     ft_strjoin.c    ft_strnstr.c 	ft_lstnew.c \
		ft_is_blank.c    ft_memmove.c    ft_strchr.c     ft_strlcat.c    ft_strrchr.c 	ft_lstdelone.c \
		ft_isdigit.c    ft_memset.c     ft_strclr.c     ft_strlen.c     ft_strrev.c 	ft_lstdel.c \
		ft_isprint.c    ft_putchar.c    ft_strcmp.c     ft_strmap.c     ft_strsplit.c 	ft_lstiter.c \
		ft_itoa.c       ft_putchar_fd.c ft_strcpy.c     ft_strmapi.c    ft_strstr.c		ft_lstadd.c \
		ft_lstmap.c		ft_joinfree.c	ft_lstpush.c	ft_lstdelfirst.c				ft_lstremoveone.c \
		my_free.c		ft_makestr.c	ft_nbcar.c		ft_strjoinfree.c				get_next_line.c\
	    ft_putnstr.c	ft_putnbr_base.c				ft_lstlen.c		ft_lstshift.c \
	ft_lstinsert.c		ft_lstmergesort.c				ft_lstrev.c		ft_lstcpy.c		ft_strrep.c \
	ft_atol.c	ft_str_is.c ft_memrev.c

D_OBJ = ./temporary

PRINTF = ./printf

OBJECTS= $(addprefix $(D_OBJ)/,$(SRCS:.c=.o))

HEADER= ../includes

all: $(NAME)

$(NAME) : $(OBJECTS)
	@ar -crs $(NAME) $(OBJECTS)
	@echo "\033[32m[OK]  libft.a created\n\033[0m"

$(D_OBJ)/%.o : %.c
	@mkdir -p temporary
	@$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<


clean: 
	@echo "\033[34mRemoval of .o files of libft ...\033[0m"
	@echo
	@rm -rf $(D_OBJ)
	@echo "\033[31mFiles .o are deleted\n\033[0m"

fclean:
	@echo "\033[34mRemoval of .o files of libft ...\033[0m"
	@echo
	@rm -rf $(D_OBJ)
	@echo "\033[31mFiles .o are deleted\n\033[0m"
	@echo "\033[33mRemoval of $(NAME)...\033[0m"
	@rm -f $(NAME)
	@echo "\033[31m[DEL]  libft.a supprime\n\033[0m"

re: fclean all

.PHONY : clean re all fclean
