/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:14 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/27 15:18:29 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

/* Includes */

# include <termcap.h>

# include "libft.h"
# include "general.h"
# include "state.h"
# include "autocomplete.h"

/* Constants */

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

/* clipboard.c */
t_input_result	cut_word(t_state *state);
t_input_result	cut_to_cursor(t_state *state);
t_input_result	cut_from_cursor(t_state *state);
t_input_result	paste(t_state *state);

/* ctrl_d.c */
int				ctrl_d(t_state *state);

/* input.c */
t_input_result	get_input(t_state *state);

/* input_configuration.c */
int				configure_input(t_state *state);
int				set_input_config(t_state *state);
int				set_orig_config(t_state *state);

/* input_handlers.c */
t_input_result	handle_key(char *buf, t_state *state);

/* movement.c */
int				check_movement(char *buf, t_state *state);

/* movement_alt.c */
int				handle_alt_left_right(char buf[BUF_SIZE], t_state *state);
int				handle_alt_up(char buf[BUF_SIZE], t_state *state);
int				handle_alt_down(char buf[BUF_SIZE], t_state *state);

#endif
