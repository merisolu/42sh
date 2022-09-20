/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 14:52:18 by amann             #+#    #+#             */
/*   Updated: 2022/09/20 14:54:55 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/***** HEADER FILES *****/

# include "../include/libft.h"
# include <stdarg.h>

/***** MACROS *****/

# define TRUE 1
# define FALSE 0
# define ZERO_LONG_DOUBLE 0.0L
# define BASE_TWO 2
# define BASE_TEN 10
# define BASE_EIGHT 8
# define BASE_SIXTEEN 16
# define SPACE 32
# define CONV_CHARS "bcdfinouxXps"

/***** COLOUR MACROS *****/

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET_COLOUR "\033[0m"

/***** STRUCT PROTOTYPING *****/

typedef struct s_width
{
	int				prec;
	int				width;
	unsigned int	prec_set;
}					t_width;

typedef struct s_conv
{
	unsigned int	percent;
	unsigned int	numeric;
	unsigned int	neg;
	unsigned int	d;
	unsigned int	o;
	unsigned int	u;
	unsigned int	x;
	unsigned int	big_x;
	unsigned int	f;
	unsigned int	b;
	unsigned int	n;
	unsigned int	p;
	unsigned int	c;
	unsigned int	s;
}					t_conv;

typedef struct s_flags
{
	unsigned int	h;
	unsigned int	hh;
	unsigned int	l;
	unsigned int	ll;
	unsigned int	big_l;
	unsigned int	z;
	unsigned int	hash;
	unsigned int	zero;
	unsigned int	nil;
	unsigned int	left;
	unsigned int	plus;
	unsigned int	space;
	t_conv			conv;
	t_width			width;
}					t_flags;

/***** FUNCTION PROTOTYPING *****/

/* ft_printf.c */
int			ft_printf(const char *s, ...);
int			ft_dprintf(int fd, const char *s, ...);

/* ft_printf_control.c */
void		ft_printf_ctrl(const char *s, va_list lst, size_t *p_i, int *p_ret);

/* set_flags.c */
void		set_flags_and_length(const char *s, t_flags *flag, int *h_i);
void		initialise_structs(t_flags *flag);

/* width_precision.c */
void		set_width_prec(const char *s, t_flags *data, int *ctrl_i,	\
				va_list lst);

/* conversion_control.c */
char		*conversion_ctrl(const char *s, va_list lst, t_flags *flag,	\
				int *p_ret);

/* set_conv_type.c */
void		set_conv_type(char c, t_conv *conv);

/* numeric_conversion.c */
void		numeric_conv_dispatcher(char c, va_list lst, char **res,	\
				t_flags *flags);

/* signed_conversion_handlers.c */
char		*handle_ll(long long ll_x, t_flags *flag);
char		*handle_l(long l_x, t_flags *flag);
char		*handle_h(int x, t_flags *flag);
char		*handle_hh(int x, t_flags *flag);
char		*handle_int(int x, t_flags *flag);

/* add_sign.c */
char		*add_sign(char *res);

/* unsigned_conversion_handlers.c */
char		*handle_ull(unsigned long long ll_x, t_flags *flag, int base);
char		*handle_ul(unsigned long l_x, t_flags *flag, int base);
char		*handle_uh(unsigned int x, t_flags *flag, int base);
char		*handle_uhh(unsigned int x, t_flags *flag, int base);
char		*handle_uint(unsigned int x, t_flags *flag, int base);

/* z_conversions.c */
char		*handle_zd(ssize_t x, t_flags *flag);
char		*handle_zu(size_t x, t_flags *flag, int base);

/* n_conversion.c */
void		convert_n(va_list lst, t_flags *flag, int *p_ret);

/* handle_double.c */
char		*convert_double(va_list lst, t_flags *flag);

/* double_helpers.c */
char		*neg_float_handler(char *res, t_flags *flag);
char		*rounding_algo(char *res, size_t prec);

/* double_helpers2.c */
void		set_x(va_list lst, t_flags *flag, long double *x);

/* chop_chop.c */
void		chop_chop(char **res_str, size_t prec, unsigned int hash);

/* flag_control.c */
char		*flag_control(char *res, t_flags flag);

/*	decimal_conv.c */
char		*convert_digit(va_list lst, t_flags *flag);
char		*convert_unsigned(va_list lst, t_flags *flag);

/* hash_flag.c */
char		*handle_hash(char *res, t_flags flag);

/* plus_flag.c */
char		*handle_plus(char *res, t_flags flag, int len);

/* zero_flag.c */
char		*handle_zero(char *res, t_flags flag);

/* print_result.c */
void		print_result(char *s, t_flags flag, int *printf_res);

/* print_result_functions.c */
void		precision_helper(char *res, char *new, t_width w, t_flags flag);
char		*set_memory(char *res, t_width w, t_flags flag);

/* ft_printf_putstr.c */
void		ft_printf_putstr(char const *str, int *printf_res, t_flags flag);
void		ft_printf_putchar(char const *str, size_t i, int *printf_res);

/* colours.c */
void		check_colour(const char *s, size_t *cursor, int *printf_ret);
#endif
