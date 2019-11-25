/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrizon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 11:15:13 by tbrizon           #+#    #+#             */
/*   Updated: 2019/08/14 16:33:38 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** -------------------------- External Headers --------------------------------
*/

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>

/*
** -------------------------- Defines -----------------------------------------
*/

# define FT_PRINTF_H
# define ON(X, Y) X |= Y
# define OFF(X, Y) X &= ~Y
# define IS_ON(X, Y)  X & Y
# define COMP(A, B) ft_strequ(A, B)
# define ZERO 1
# define MOINS 2
# define PLUS 4
# define BLANK 8
# define SHARP 16
# define STAR 	32
# define BUFF_SIZE 500
# define NB_CAR 16400

/*
** -------------------------- Colors Definition --------------------------------
*/

# define PF_RED			"\033[31m"
# define PF_GREEN		"\033[32m"
# define PF_YELLOW		"\033[33m"
# define PF_BLUE		"\033[34m"
# define PF_PURPLE		"\033[35m"
# define PF_CYAN		"\033[36m"
# define PF_WHITE		"\033[37m"
# define PF_EOC			"\033[0m"

/*
** -------------------------- Structures --------------------------------------
*/

typedef struct		s_print
{
	int				arg_len;
	int				padding;
	int				flags;
	int				prec;
	int				strlen;
}					t_print;

typedef struct		s_bloc
{
	unsigned char	flags;
	int				mfw;
	int				prec;
	char			type;
	char			modif[3];
}					t_bloc;

typedef struct		s_buf
{
	char			tab[BUFF_SIZE];
	int				i;
	int				cmpt;
	int				fd;
}					t_buf;

typedef struct		s_mask
{
	char			signe;
	short			e;
	unsigned long	l;
}					t_mask;

typedef struct		s_float
{
	char			p_int[NB_CAR];
	char			p_dec[NB_CAR];
	t_mask			mask;
}					t_float;

typedef struct		s_exposant
{
	char			p_int;
	char			p_dec[NB_CAR];
	int				exp;
	char			signe_exp;
	char			signe;
	int				len;
}					t_exp;

typedef struct		s_opp
{
	char			c;
	void			(*f)(t_bloc*, va_list, t_buf*);
}					t_opp;

/*
** --------------------- Fonction dispatcher -----------------------------------
*/

void				dispatcher(t_bloc *bdi, va_list ap, t_buf *buf);
void				ft_is_int(t_bloc *bdi, va_list ap, t_buf *buf);
void				ft_is_hexa(t_bloc *bdi, va_list ap, t_buf *buf);
void				ft_is_oct(t_bloc *bdi, va_list ap, t_buf *buf);
void				ft_is_char(t_bloc *bdi, va_list ap, t_buf *buf);
void				ft_is_uns(t_bloc *bdi, va_list ap, t_buf *buf);
void				ft_is_add(t_bloc *bdi, va_list ap, t_buf *buf);
void				ft_is_str(t_bloc *bdi, va_list ap, t_buf *buf);
void				ft_is_bin(t_bloc *bdi, va_list ap, t_buf *buf);
void				ft_is_float(t_bloc *bdi, va_list ap, t_buf *buf);
void				ft_is_exp(t_bloc *bdi, va_list ap, t_buf *buf);
void				ft_is_fd(t_bloc *bdi, va_list ap, t_buf *buf);

/*
** -------------------------- Functions parsing --------------------------------
*/

int					ft_parsing(const char **str, t_bloc *bloc,
	t_buf *buf, va_list ap);
void				ft_parsing_flags(const char **str, unsigned char *flags);
void				ft_parsing_mfw(const char **str, int *mfw);
void				ft_parsing_precision(const char **str,
	int *prec, va_list ap);
void				ft_parsing_modif(const char **str, char *modif);
void				ft_parsing_arg(const char **str, char *type);
void				star(const char **str, t_bloc *bdi, va_list ap);
int					jumpin(const char **str, t_bloc *bloc, va_list ap);

/*
** -------------------------- Functions flags -----------------------------
*/

void				rules_flag(unsigned char *flags, char type, int prec);
void				turnoff_nb(unsigned char *flags);

/*
** ---------------------------Functions print-------------------------------
*/

void				print_pad(int zero, int nb);
void				first_printfl(double f, int *cmpt, int prec);
void				print_prec(int nb);

/*
** -------------------------- Functions is a thing -----------------------------
*/

int					ft_is_in(const char **str);
int					ft_is_type(const char **str);
int					is_nombre(char type);
int					is_add(char type);
int					is_base(char type);
int					is_char(char type);

/*
** ------------------------fonction fill buff ---------------------------
*/

void				fill_buff(t_buf *buf, char *str);
void				char_buf(t_buf *buf, char c, int nb);
void				empty_buf(t_buf *buf);
void				str_buf(t_buf *b, char *s, int n);
void				fill_color(t_buf *buf, char *color, int n);
void				ltoa_base(t_buf *buf, long l, int b, int prec);
void				ultoa_base(t_buf *buf, unsigned long ul, int b, int prec);
void				ultoa_maj(t_buf *buf, unsigned long ul, int b, int prec);
void				exptoa(t_buf *buf, int e);

/*
** -------------------------- Function init -------------------------------
*/

void				initialise_bloc(t_bloc *bdi);
void				initialise_buf(t_buf *buf);
void				initialise_print(t_print *print);

/*
** -------------------------- printf ---------------------------------------
*/

int					ft_printf(const char *format, ...);

/*
** ---------------------Fonction nb_car-------------------------------------
*/

int					ft_nbcarint(int nb);
int					ft_nbcarlong(long int nb);
int					ft_nbcar_hd(unsigned long int nb, int prec);
int					ft_nbcarbase(unsigned long int nb, int base);
void				print_prec(int nb);
void				ft_putadd(unsigned long int nb, unsigned int b);

/*
** ---------------------------Fonctions float ----------------------------
*/

int					apply_round(char *tab, int base, int pc);
int					arround_int(char *tabint, char *tabf);
int					get_signe(unsigned long l);
int					get_exposant(unsigned long l);
void				add_int(char *src, const char *add);
void				add_dec(char *src, const char *add);
void				make_mask(unsigned long *l, t_mask *mask, int lg);
void				make_fl(t_float *fl, va_list ap, int lg, int prec);
void				get_strfl(t_float *f, t_mask mask, int lg);
int					make_arrondi(t_float *fl, int prec);
int					calc_exp(t_float *f, t_exp *exp);
void				make_exp(t_float *f, t_exp *e);
void				arrondi_expint(t_exp *e);
int					only_zero(char *tab);
int					make_arrondiexp(t_exp *e, int prec);
int					apply_roundex(char *tab, int base, int pc);

#endif
