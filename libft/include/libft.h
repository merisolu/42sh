/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:24:04 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/29 15:47:20 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/stat.h>
# include <stdarg.h>

/* Buffer size for ft_get_next_line(). */
# define GNL_BUFF_SIZE 32

/* Colors */

# define COLOR_RESET "\033[0m"

# define TEXT_WHITE "\033[0;37m"
# define TEXT_BLACK "\033[0;30m"
# define TEXT_RED "\033[0;31m"
# define TEXT_YELLOW "\033[0;33m"
# define TEXT_GREEN "\033[0;32m"
# define TEXT_CYAN "\033[0;36m"
# define TEXT_BLUE "\033[0;34m"
# define TEXT_MAGENTA "\033[0;35m"

# define BG_WHITE "\033[0;47m"
# define BG_BLACK "\033[0;40m"
# define BG_RED "\033[0;41m"
# define BG_YELLOW "\033[0;43m"
# define BG_GREEN "\033[0;42m"
# define BG_CYAN "\033[0;46m"
# define BG_BLUE "\033[0;44m"
# define BG_MAGENTA "\033[0;45m"

/* Bold variants. */

# define BTEXT_WHITE "\033[37;1m"
# define BTEXT_BLACK "\033[30;1m"
# define BTEXT_RED "\033[31;1m"
# define BTEXT_YELLOW "\033[33;1m"
# define BTEXT_GREEN "\033[32;1m"
# define BTEXT_CYAN "\033[36;1m"
# define BTEXT_BLUE "\033[34;1m"
# define BTEXT_MAGENTA "\033[35;1m"

# define BBG_WHITE "\033[47;1m"
# define BBG_BLACK "\033[40;1m"
# define BBG_RED "\033[41;1m"
# define BBG_YELLOW "\033[43;1m"
# define BBG_GREEN "\033[42;1m"
# define BBG_CYAN "\033[46;1m"
# define BBG_BLUE "\033[44;1m"
# define BBG_MAGENTA "\033[45;1m"

/* Linked list struct. */
typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef unsigned long long	t_ull;

/* (ft_printf) Union for accessing specific bytes in a double. */
union	u_double_bytes {
	double			number;
	unsigned char	bytes[sizeof(double)];
};

/* (ft_printf) Union for accessing specific bytes in a long double. */
union	u_ldouble_bytes {
	long double		number;
	unsigned char	bytes[sizeof(long double)];
};

/* Char functions. */
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isprint(int c);
int			ft_isascii(int c);
int			ft_is_whitespace(char c);

/* String functions. */
size_t		ft_strlen(const char *c);
int			ft_strlen_int(const char *c);
char		*ft_strdup(const char *s1);
char		*ft_strndup(const char *s, size_t n);
char		*ft_strnew(size_t size);
void		ft_strdel(char **as);
char		*ft_strdelchar(const char *s, size_t i);
char		*ft_strdelword(const char *s, size_t i, size_t *del_count);
void		ft_strclr(char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strncpy(char *dst, const char *src, size_t len);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strncat(char *s1, const char *s2, size_t n);
char		*ft_strcat(char *s1, const char *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *stack, const char *n, size_t len);
char		*ft_strstr(const char *stack, const char *n);
int			ft_strnequ(char const *s1, char const *s2, size_t n);
int			ft_strequ(char const *s1, char const *s2);
int			ft_strendequ(char const *s1, char const *s2);
void		ft_striter(char *s, void (*f)(char *));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strmap(char const *s, char (*f)(char));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strsub(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strnjoin(char const *s1, char const *s2, size_t n);
char		*ft_strjoinfree(char const *s1, char const *s2);
char		*ft_strnjoinfree(char const *s1, char const *s2, size_t n);
char		*ft_strins(const char *s, size_t i, char c);
char		*ft_strtrim(char const *s);
char		**ft_strsplit(char const *s, char c);
char		*ft_strtolower(char *s);
char		*ft_strtoupper(char *s);
int			ft_strisempty(const char *str);
size_t		ft_strchrcount(char *str, char c);
size_t		ft_strchrrcount(char *str, char c, size_t start);

/* Mem functions. */
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memichr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memalloc(size_t size);
void		ft_memdel(void **ap);

void		*ft_realloc(void *pointer, size_t size, size_t old_size);

void		ft_bzero(void *s, size_t n);

/* String and char put functions. */
void		ft_putchar_fd(char c, int fd);
void		ft_putcharn_fd(char c, int n, int fd);
void		ft_putstr_fd(char const *s, int fd);
void		ft_putstrn_fd(char const *s, const int n, int fd);
void		ft_putendl_fd(char const *s, int fd);
void		ft_putchar(char c);
void		ft_putcharn(char c, int n);
void		ft_putstr(char const *s);
void		ft_putstrn(char const *s, const int n);
void		ft_putendl(char const *s);

/* Numerical put functions. */
void		ft_putnbr(int n);
void		ft_putnbr_llong(long long n);
void		ft_putnbr_ullong(t_ull n);
void		ft_putnbr_fd(int n, int fd);
void		ft_putnbr_llong_fd(long long n, int fd);
void		ft_putnbr_ullong_fd(t_ull n, int fd);

void		ft_putnbrn(int n, int len);
void		ft_putnbrn_llong(long long n, int len);
void		ft_putnbrn_ullong(t_ull n, int len);
void		ft_putnbrn_fd(int n, int len, int fd);
void		ft_putnbrn_llong_fd(long long n, int len, int fd);
void		ft_putnbrn_ullong_fd(t_ull n, int len, int fd);

/* Itoas */
char		*ft_itoa(int n);
char		*ft_itoa_uint(unsigned int n);
char		*ft_itoa_llong(long long n);
char		*ft_itoa_ullong(t_ull n);

char		*ft_itoa_base(int n, int base);
char		*ft_itoa_uint_base(unsigned int n, unsigned int base);
char		*ft_itoa_llong_base(long long n, int base);
char		*ft_itoa_ullong_base(t_ull n, int base);

int			ft_atoi(const char *str);

/* Numerical comparisons. */
int			ft_abs(int i);
long		ft_abs_long(long i);
long long	ft_abs_llong(long long i);
double		ft_abs_double(double f);
long double	ft_abs_ldouble(long double f);

int			ft_min(int i1, int i2);
long		ft_min_long(long l1, long l2);
long long	ft_min_llong(long long l1, long long l2);
t_ull		ft_min_ullong(t_ull l1, t_ull l2);
size_t		ft_min_size_t(size_t s1, size_t s2);

int			ft_max(int i1, int i2);
long		ft_max_long(long l1, long l2);
long long	ft_max_llong(long long l1, long long l2);
t_ull		ft_max_ullong(t_ull l1, t_ull l2);
size_t		ft_max_size_t(size_t s1, size_t s2);

int			ft_clamp(int value, int min, int max);

/* Math functions. */
int			ft_pow(int n, unsigned int pow);
long		ft_pow_long(long n, unsigned int pow);
long long	ft_pow_llong(long long n, unsigned int pow);
double		ft_pow_double(double n, int pow);
long double	ft_pow_ldouble(long double n, int pow);

double		ft_fmod(double f, double div);
long double	ft_fmodl(long double f, long double div);

double		ft_modf(double f, double *i);
long double	ft_modfl(long double f, long double *i);

double		ft_frexp(double value, int *exp);
long double	ft_frexpl(long double value, int *exp);

/* Float specific functions. */
int			ft_getexponent(double n);
int			ft_getexponent_long(long double n);

double		ft_getmantissa(double n);
long double	ft_getmantissa_long(long double n);

int			ft_isinfinite(double n);
int			ft_isinfinite_long(long double n);

int			ft_isnan(double n);
int			ft_isnan_long(long double n);

long long	ft_round(double f);
long long	ft_round_long(long double f);

/* Signs */
int			ft_getsign(int c);
int			ft_getsign_llong(long long c);
int			ft_getsign_double(double c);
int			ft_getsign_ldouble(long double c);

/* Digit counts. */
int			ft_getdigits(int c);
int			ft_getdigits_uint(unsigned int n);
int			ft_getdigits_llong(long long c);
int			ft_getdigits_ullong(t_ull c);

int			ft_getdigits_base(int c, int base);
int			ft_getdigits_uint_base(unsigned int c, int base);
int			ft_getdigits_llong_base(long long c, int base);
int			ft_getdigits_ullong_base(t_ull c, int base);

int			ft_getnumlen(int c);
int			ft_getnumlen_uint(unsigned int n);
int			ft_getnumlen_llong(long long c);
int			ft_getnumlen_ullong(t_ull c);

/* Array functions. */
void		*ft_free_array(void **array, size_t size);
void		ft_free_array_elements(void **array, size_t size);
void		*ft_free_null_array(void **array);
void		ft_free_null_array_elements(void **array);

size_t		ft_null_array_len(void **array);

int			ft_copy_null_array(void **dst, void **src, void *(*cpy)(void *));
int			ft_dup_null_array(void **src, void ***result, void *(*cpy)(void *));
int			ft_resize_null_array(void ***array, size_t size);
int			ft_add_to_null_array(void ***array, void *new);
int			ft_remove_from_null_array(void ***array, void *removeable);

void		ft_rev_array(void **array, size_t size);
void		ft_rev_null_array(void **array);

void		ft_sort(void **array, size_t len, int (*c)(void *, void *));

/* List functions. */
t_list		*ft_lstnew(void const *content, size_t content_size);
void		ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void		ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void		ft_lstadd(t_list **alst, t_list *new);
void		ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

size_t		ft_dstchr(const char *s, char c, size_t max);
size_t		ft_dstrchr(const char *s, char c, size_t start);

/* Path functions. */
int			ft_is_hidden(const char *path);
int			ft_path_is_absolute(const char *path);
int			ft_path_is_within_limits(const char *path);

int			ft_is_dir(const char *path);
int			ft_points_to_dir(const char *path);

int			ft_is_file(const char *path);
int			ft_points_to_file(const char *path);

void		ft_path_join(const char *a, const char *b, char **dst);

char		*ft_get_path_name_ptr(const char *path);

char		*ft_get_path_parent(const char *path);

int			ft_path_is_self_or_parent(const char *path);

int			ft_path_has_valid_end(const char *path);
int			ft_path_has_valid_link(const char *path);

void		ft_normalize_path(const char *path, char **dst);

/* GNL */
int			ft_get_next_line(const int fd, char **line);

/* ft_printf */
int			ft_printf(const char *format, ...);
int			ft_dprintf(int fd, const char *format, ...);
int			ft_vdprintf(int fd, const char *format, va_list lst);

#endif
