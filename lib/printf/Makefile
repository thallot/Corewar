C = gcc
NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror
LIBFT = libft
SRC = src
DIR_O = obj
HEADER = includes

SOURCES = ft_printf.c \
		  print_int.c \
		  print_string.c \
			print_pointer.c \
			print_float.c \
			print_binary.c \
			arg.c \
			flag.c \
			get_arg.c \
		  strjoin.c \
		  itoa_base.c \
		  ft_pow.c \
		  integer.c \
		  convert.c \
		  caster.c \
		  free.c \
		  functions.c \
			putter.c \
			exception.c \
			except.c \
			itoa.c \
			float.c \
			\
			ft_isdigit.c \
			ft_itoa.c \
			ft_memalloc.c \
			ft_memdel.c \
			ft_putchar.c \
			ft_putstr.c \
			ft_putnbr.c \
			ft_strdup.c \
			ft_strchr.c \
			ft_strnew.c \
			ft_strsub.c \
			ft_abs.c \
			ft_bzero.c \
			ft_strlen.c \
			ft_strncpy.c \
			ft_memset.c

SRCS = $(addprefix $(SRC)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

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

$(NAME): $(OBJS)
	@echo "$(GREEN)[OK] $(_BLUE)Tous les objets de $(WHITE)$(NAME) $(_BLUE)sont generes !\r"
	@echo "$(GREEN)[OK] $(_BLUE)Compilation de $(WHITE)$(NAME)"
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(DIR_O)/%.o: $(SRC)/%.c
	@mkdir -p obj
	@$(CC) $(CFLAGS) -c -o $@ $< && printf "$(GREEN)[OK] $(_BLUE)Generation de $(WHITE)%-50s\r" "$@" || \
	(echo "$(_RED)[ERREUR]$(_GRAY) Une est erreur est survenue sur $(WHITE)$<$(RED), $(WHITE)$(NAME)$(RED) non compilé(e)\n" && exit 1)

exe: all
	gcc $(NAME) src/main.c -o ft_printf

norme:
	norminette ./includes/
	@echo
	norminette ./src/

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)

fclean: clean
	@echo "$(GREEN)[OK]$(RED) Supression de $(WHITE)$(NAME)\n"
	@rm -f $(NAME)

re: fclean all
