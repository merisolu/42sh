/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:14 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/21 13:35:46 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

/* Includes */

# include <termcap.h>

# include "libft.h"
# include "general.h"
# include "autocomplete.h"

/* Keys */

# define ARROW_UP "\x1B[A"
# define ARROW_DOWN "\x1B[B"
# define ARROW_LEFT "\x1B[D"
# define ARROW_RIGHT "\x1B[C"
# define ARROW_UP_ALT "\x1B[1;3A"
# define ARROW_DOWN_ALT "\x1B[1;3B"
# define ARROW_LEFT_ALT "\033b"
# define ARROW_RIGHT_ALT "\033f"
# define BACKSPACE "\x7F"
# define DELETE "\x1B[3~"
# define HOME_KEY "\x1B[H"
# define END_KEY "\x1B[F"
# define TAB "\t"

/* Key sequences */

# define CTRL_B "\x02"
# define CTRL_D "\x04"
# define CTRL_F "\x06"
# define CTRL_K "\x0b"
# define CTRL_P "\x10"
# define CTRL_U "\x15"
# define CTRL_W "\x17"
# define CTRL_Y "\x19"

/* Types */

typedef enum e_input_result
{
	INPUT_CALLED_FOR_EXIT = -1,
	INPUT_NO_MARK_FOUND = 0,
	INPUT_MARK_FOUND = 1,
	INPUT_FOUND_RESERVED_SEQUENCE = 2,
	INPUT_READ_ERROR = 3,
	INPUT_NOTHING_READ = 4
}	t_input_result;

typedef int		t_key_handler(t_input_context *ctx);

typedef struct s_key_handler_dispatch
{
	char			*activator;
	t_key_handler	*run;
}	t_key_handler_dispatch;

/* Files */

/* clipboard_copy.c */
int				copy_word(t_input_context *ctx);
int				copy_to_cursor(t_input_context *ctx);
int				copy_from_cursor(t_input_context *ctx);

/* clipboard_cut.c */
int				cut_word(t_input_context *ctx);
int				cut_to_cursor(t_input_context *ctx);
int				cut_from_cursor(t_input_context *ctx);

/* clipboard_paste.c */
int				paste(t_input_context *ctx);

/* clipboard_utils.c */
void			get_word_at_cursor(t_input_context *ctx, \
size_t *start, size_t *end);

/* ctrl_d.c */
int				ctrl_d(t_input_context *context);

/* input.c */
t_input_result	get_input(t_input_context *ctx);

/* input_handlers.c */
int				handle_key(char *buffer, t_input_context *ctx);

/* input_context.c */
int				input_context_set(t_input_context *context, \
t_input_initializer *init);
void			input_context_free(t_input_context *context);

/* input_utils.c */
int				is_inhibited(char *input);
void			append_input(t_input_context *ctx, char character);
int				check_for_reserved_sequence(char *buffer, t_input_context *ctx);

/* movement.c */
int				handle_left(t_input_context *ctx);
int				handle_right(t_input_context *ctx);
int				handle_home(t_input_context *ctx);
int				handle_end(t_input_context *ctx);

/* movement_alt.c */
int				handle_alt_left(t_input_context *ctx);
int				handle_alt_right(t_input_context *ctx);
int				handle_alt_up(t_input_context *ctx);
int				handle_alt_down(t_input_context *ctx);

#endif
