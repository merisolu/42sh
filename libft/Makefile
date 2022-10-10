# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/28 16:25:00 by jumanner          #+#    #+#              #
#    Updated: 2022/10/10 10:25:17 by jumanner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

INCLUDE_DIR = ./include

SRC_FILES = ft_tolower.c ft_toupper.c \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isprint.c ft_isascii.c \
		ft_strlen.c ft_strdup.c ft_strndup.c ft_strnew.c ft_strdel.c ft_strdelchar.c ft_strdelword.c ft_strclr.c \
		ft_strncmp.c ft_strcmp.c \
		ft_strncpy.c ft_strcpy.c ft_strncat.c ft_strcat.c ft_strlcat.c \
		ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strstr.c ft_strnequ.c ft_strequ.c \
		ft_strins.c \
		ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c \
		ft_strtolower.c ft_strtoupper.c ft_strisempty.c \
		ft_strcharcount.c \
		ft_memset.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memichr.c ft_memcmp.c ft_memalloc.c ft_memdel.c \
		ft_putchar_fd.c ft_putcharn_fd.c ft_putstr_fd.c ft_putstrn_fd.c ft_putendl_fd.c ft_putchar.c ft_putcharn.c ft_putstr.c ft_putstrn.c ft_putendl.c \
		ft_putnbr_fd.c ft_putnbr.c ft_putnbrn_fd.c ft_putnbrn.c \
		ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c \
		ft_itoa.c ft_itoa_base.c ft_atoi.c \
		ft_getdigits.c ft_getdigits_base.c ft_getnumlen.c ft_getsign.c \
		ft_bzero.c ft_realloc.c \
		ft_sort.c \
		ft_max.c ft_min.c ft_clamp.c \
		ft_abs.c ft_abs_float.c \
		ft_pow.c \
		ft_fmod.c ft_modf.c ft_frexp.c ft_round.c ft_getexponent.c ft_getmantissa.c ft_isinfinite.c ft_isnan.c \
		ft_is_whitespace.c \
		ft_free_array.c ft_rev_array.c ft_null_array.c ft_null_array_element.c ft_null_array_properties.c ft_null_array_free.c \
		ft_dstchr.c \
		ft_get_next_line.c \
		ft_file.c ft_dir.c ft_path.c ft_path_properties.c ft_path_validity.c
SRC_DIR = ./src
SRCS := $(patsubst %, $(SRC_DIR)/%, $(SRC_FILES))

OBJ_DIR = ./obj
OBJS := $(patsubst %, $(OBJ_DIR)/%, $(SRC_FILES:.c=.o))

FT_PRINTF_DIR = ./ft_printf

FT_PRINTF_SRC_FILES = conversion_control.c ft_printf.c set_flags.c			\
		print_result.c hash_flag.c flag_control.c numeric_conversion.c		\
		width_precision.c plus_flag.c handle_double.c ft_printf_putstr.c	\
		double_helpers.c double_helpers2.c signed_conversion_handlers.c		\
		unsigned_conversion_handlers.c add_sign.c n_conversion.c			\
		set_conv_type.c colours.c ft_printf_control.c chop_chop.c			\
		print_result_functions.c zero_flag.c z_conversions.c
FT_PRINTF_SRC_DIR = $(FT_PRINTF_DIR)/src
FT_PRINTF_SRCS := $(patsubst %, $(FT_PRINTF_SRC_DIR)/%, $(FT_PRINTF_SRC_FILES))
FT_PRINTF_OBJ_DIR = $(FT_PRINTF_DIR)/obj
FT_PRINTF_OBJS := $(patsubst %, $(FT_PRINTF_OBJ_DIR)/%, $(FT_PRINTF_SRC_FILES:.c=.o))
FT_PRINTF_INCLUDE_DIR = $(FT_PRINTF_DIR)/include

GCC_FLAGS = -O2 -Wall -Wextra -Werror

$(NAME): $(OBJS) $(FT_PRINTF_OBJS)
	ar rcs $(NAME) $(OBJS) $(FT_PRINTF_OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(GCC_FLAGS) -I $(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(FT_PRINTF_OBJ_DIR)/%.o: $(FT_PRINTF_SRC_DIR)/%.c | $(FT_PRINTF_OBJ_DIR)
	$(CC) $(GCC_FLAGS) -I $(INCLUDE_DIR) -I $(FT_PRINTF_INCLUDE_DIR) -c $< -o $@

$(FT_PRINTF_OBJ_DIR):
	mkdir -p $(FT_PRINTF_OBJ_DIR)

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(FT_PRINTF_OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
