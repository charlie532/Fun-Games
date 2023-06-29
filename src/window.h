#ifndef __GBOX_WINDOW_H__
#define __GBOX_WINDOW_H__

#include "preview.h"
#include "tictactoe/ttt-view.h"
#include "connect-four/cf-view.h"
#include "mill/mill-view.h"
#include "checkers/chks-view.h"
#include "css-code.h"
#include <gtk/gtk.h>

#define GBOX_SIZE_WIN_X 670
#define GBOX_SIZE_WIN_Y 560

#define GBOX_SIZE_TTT_X 500
#define GBOX_SIZE_TTT_Y 500
#define GBOX_TITLE_PREV_TTT "Tic Tac Toe"
#define GBOX_TITLE_GAME_TTT "ttt"

#define GBOX_SIZE_CF_X 650
#define GBOX_SIZE_CF_Y 550
#define GBOX_TITLE_PREV_CF "Connect Four"
#define GBOX_TITLE_GAME_CF "cf"

#define GBOX_SIZE_MILL_X 600
#define GBOX_SIZE_MILL_Y 600
#define GBOX_TITLE_PREV_MILL "Mill"
#define GBOX_TITLE_GAME_MILL "mill"

#define GBOX_SIZE_CHKS_X 600
#define GBOX_SIZE_CHKS_Y 600
#define GBOX_TITLE_PREV_CHKS "Checkers"
#define GBOX_TITLE_GAME_CHKS "chks"

#define GBOX_TITLE_MAIN "GameBox"

#define GBOX_CLASS_WINDOW "gbox-window"

#define GAME_NUM 4


typedef enum {
	GBOX_GAME_TTT,
	GBOX_GAME_CF,
	GBOX_GAME_MILL,
	GBOX_GAME_CHKS,
} GBoxGame;

class GBoxWindow {
private:
	/* Container */
	GtkWidget *self;
	GtkWidget *hbar;
	GtkWidget *grid;
	GtkWidget *sidebar;
	GtkWidget *stack_main;
	GtkWidget *stack_prev;
	GtkWidget *stack_game;

	/* Header bar widgets */
	GtkWidget *btn_back;
	GtkWidget *btn_new;

	/* Previews */
	GBoxPreview *prev_ttt;
	GBoxPreview *prev_cf;
	GBoxPreview *prev_mill;
	GBoxPreview *prev_chks;

	/* Views (Games) */
	TttView  *view_ttt;
	CfView   *view_cf;
	MillView *view_mill;
	ChksView *view_chks;

	/* States */
	GBoxGame active_game;

public:
	GBoxGame get_active_game();
	void set_active_game(GBoxGame);
	void gbox_window_add_interface();
	TttView *get_view_ttt();
	CfView   *get_view_cf();
	MillView *get_view_mill();
	ChksView *get_view_chks();
	GtkWidget *get_stack_main();
	GtkWidget *get_stack_prev();
	GtkWidget *get_stack_game();
	GtkWidget *get_btn_back();
	GtkWidget *get_btn_new();
	GtkWidget *get_hbar();
	GtkWidget *get_grid();
    GtkWidget *gbox_window_get();
	GBoxWindow();
};

#endif /* __GBOX_WINDOW_H__ */
