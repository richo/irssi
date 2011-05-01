#ifndef __TERM_H
#define __TERM_H

typedef struct _TERM_WINDOW TERM_WINDOW;

/* text attributes */
#define ATTR_RESETFG	0x010000
#define ATTR_RESETBG	0x020000
#define ATTR_BOLD	0x040000
#define ATTR_BLINK      0x080000
#define ATTR_UNDERLINE	0x100000
#define ATTR_REVERSE	0x200000

#define EXT_COLOR_BLACK   ( 0 )
#define EXT_COLOR_RED     ( 1 )
#define EXT_COLOR_GREEN   ( 2 )
#define EXT_COLOR_YELLOW  ( 3 )
#define EXT_COLOR_BLUE    ( 4 )
#define EXT_COLOR_MAGENTA ( 5 )
#define EXT_COLOR_CYAN    ( 6 )
#define EXT_COLOR_WHITE   ( 7 )

#define ATTR_RESET	(ATTR_RESETFG|ATTR_RESETBG)

#define ATTR_NOCOLORS (ATTR_UNDERLINE|ATTR_REVERSE|ATTR_BLINK|ATTR_BOLD)

/* terminal types */
#define TERM_TYPE_8BIT		0 /* normal 8bit text */
#define TERM_TYPE_UTF8		1
#define TERM_TYPE_BIG5		2

typedef guint32 unichar;

extern TERM_WINDOW *root_window;
extern int term_width, term_height;
extern int term_use_colors, term_type;

/* Initialize / deinitialize terminal */
int term_init(void);
void term_deinit(void);

/* Gets the current terminal size, returns TRUE if ok. */
int term_get_size(int *width, int *height);

/* Resize terminal - if width or height is negative,
   the new size is unknown and should be figured out somehow */
void term_resize(int width, int height);
void term_resize_final(int width, int height);
/* Resize the terminal if needed */
void term_resize_dirty(void);

/* Returns TRUE if terminal has colors */
int term_has_colors(void);
/* Force the colors on any way you can */
void term_force_colors(int set);

/* Clear screen */
void term_clear(void);
/* Beep */
void term_beep(void);

/* Create a new window in terminal */
TERM_WINDOW *term_window_create(int x, int y, int width, int height);
/* Destroy a terminal window */
void term_window_destroy(TERM_WINDOW *window);

/* Move/resize window */
void term_window_move(TERM_WINDOW *window, int x, int y,
		      int width, int height);
/* Clear window */
void term_window_clear(TERM_WINDOW *window);
/* Scroll window up/down */
void term_window_scroll(TERM_WINDOW *window, int count);

void term_set_color(TERM_WINDOW *window, int col);

void term_set_extended_color(TERM_WINDOW *window, int fg, int bg);

void term_move(TERM_WINDOW *window, int x, int y);
void term_addch(TERM_WINDOW *window, char chr);
void term_add_unichar(TERM_WINDOW *window, unichar chr);
void term_addstr(TERM_WINDOW *window, const char *str);
void term_clrtoeol(TERM_WINDOW *window);

void term_move_cursor(int x, int y);

void term_refresh_freeze(void);
void term_refresh_thaw(void);
void term_refresh(TERM_WINDOW *window);

void term_stop(void);

/* keyboard input handling */
void term_set_input_type(int type);
void term_gets(GArray *buffer, int *line_count);

/* internal */
void term_common_init(void);
void term_common_deinit(void);

#endif
