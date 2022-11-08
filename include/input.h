/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:14 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/08 13:41:36 by jumanner         ###   ########.fr       */
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
# define HOME_KEY "\x1B[H"
# define END_KEY "\x1B[F"
# define TAB "\t"

/* Key sequences */

# define CTRL_D "\x04"
# define CTRL_K "\x0b"
# define CTRL_U "\x15"
# define CTRL_W "\x17"
# define CTRL_Y "\x19"

/* Types */

typedef enum e_input_result
{
	INPUT_NOTHING_READ = -2,
	INPUT_READ_ERROR = -1,
	INPUT_NO_MARK_FOUND = 0,
	INPUT_MARK_FOUND = 1
}	t_input_result;

typedef int		t_key_handler(t_input_context *ctx);

typedef struct s_key_handler_dispatch
{
	char			*activator;
	t_key_handler	*run;
}	t_key_handler_dispatch;

typedef int		t_movement_handler(char buf[16], t_input_context *ctx);

typedef struct s_movement_handler_dispatch
{
	char				*activator;
	t_movement_handler	*run;
}	t_movement_handler_dispatch;

/* Files */

/* clipboard.c */
int				cut_word(t_input_context *ctx);
int				cut_to_cursor(t_input_context *ctx);
int				cut_from_cursor(t_input_context *ctx);
int				paste(t_input_context *ctx);

/* ctrl_d.c */
int				ctrl_d(t_state *state);

/* input.c */
t_input_result	get_line(t_input_context *ctx, int whole_line);

/* input_handlers.c */
int				handle_key(char *buf, t_input_context *ctx);

/* input_context.c */
int				input_context_set(t_input_context *context, \
char *start_prompt, char *multiline_prompt, char *mark);
void			input_context_free(t_input_context *context);

/* movement.c */
int				check_movement(char *buf, t_input_context *ctx);

/* movement_alt.c */
int				handle_alt_left_right(char buf[BUF_SIZE], t_input_context *ctx);
int				handle_alt_up(char buf[BUF_SIZE], t_input_context *ctx);
int				handle_alt_down(char buf[BUF_SIZE], t_input_context *ctx);

#endif
