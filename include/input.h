/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:14 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/27 14:14:28 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

/* Includes */

# include <termcap.h>
# include <dirent.h>
# include "libft.h"
# include "general.h"
# include "environment.h"
# include "built_ins.h"

/* Constants */

# define BUF_SIZE 16
# define INPUT_MAX_SIZE LINE_MAX

# define PROMPT "$> "
# define MULTILINE_PROMPT "> "

# define CC_SUSPEND VDSUSP

# if __linux__
#  undef CC_SUSPEND
#  define CC_SUSPEND VSUSP
# endif

/* Keys */

# define ARROW_UP "\x1B[A"
# define ARROW_DOWN "\x1B[B"
# define ARROW_LEFT "\x1B[D"
# define ARROW_RIGHT "\x1B[C"
# define ARROW_UP_ALT "\x1B[1;3A"
# define ARROW_DOWN_ALT "\x1B[1;3B"
# define ARROW_LEFT_ALT "\033b"
# define ARROW_RIGHT_ALT "\033f"
# define RETURN_KEY "\x0A"
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
	INPUT_NO_NEWLINE_FOUND = 0,
	INPUT_NEWLINE_FOUND = 1
}	t_input_result;

typedef t_input_result	t_key_handler(t_state *state);

typedef struct s_key_handler_dispatch
{
	char			*activator;
	t_key_handler	*run;
}	t_key_handler_dispatch;

typedef int				t_movement_handler(char buf[16], t_state *state);

typedef struct s_movement_handler_dispatch
{
	char				*activator;
	t_movement_handler	*run;
}	t_movement_handler_dispatch;

/* Files */

/* autocomplete.c */
int				autocomplete(t_state *state);

/* clipboard.c */
t_input_result	cut_word(t_state *state);
t_input_result	cut_to_cursor(t_state *state);
t_input_result	cut_from_cursor(t_state *state);
t_input_result	paste(t_state *state);

/* ctrl_d.c */
int				ctrl_d(t_state *state);

/* cursor.c */
void			save_cursor(t_state *state);
void			load_cursor(t_state *state);

/* cursor_utils.c */
void			move_cursor_to_saved_position(t_state *state);
size_t			cursor_get_column(t_state *state, size_t index);
size_t			cursor_get_row(t_state *state, size_t index);

/* history.c */
int				history_store(char *input, t_state *state);
int				history_recall(int diff, t_state *state);

/* input.c */
t_input_result	get_input(t_state *state);

/* input_configuration.c */
int				configure_input(t_state *state);
int				set_input_config(t_state *state);
int				set_orig_config(t_state *state);

/* input_handlers.c */
t_input_result	handle_key(char *buf, t_state *state);

/* input_utils.c */
size_t			input_get_row_count(t_state *state, size_t index);
void			input_get_line_properties(\
	t_state *state, size_t index, size_t *start, size_t *length);

/* movement.c */
int				check_movement(char *buf, t_state *state);

/* movement_alt.c */
int				handle_alt_left_right(char buf[BUF_SIZE], t_state *state);
int				handle_alt_up(char buf[BUF_SIZE], t_state *state);
int				handle_alt_down(char buf[BUF_SIZE], t_state *state);

#endif
