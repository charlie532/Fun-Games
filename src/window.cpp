#include "window.h"
#include <iostream>

GBoxGame GBoxWindow::get_active_game() {
    GtkStack *stack_prev = GTK_STACK(this->stack_prev);
    const gchar *title_prev = gtk_stack_get_visible_child_name(stack_prev);

    if (g_strcmp0(title_prev, GBOX_TITLE_PREV_TTT) == 0) {
        return GBOX_GAME_TTT;
    } else if (g_strcmp0(title_prev, GBOX_TITLE_PREV_CF) == 0) {
        return GBOX_GAME_CF;
    } else if (g_strcmp0(title_prev, GBOX_TITLE_PREV_MILL) == 0) {
        return GBOX_GAME_MILL;
    } else {
        return GBOX_GAME_CHKS;
    }
}

void GBoxWindow::set_active_game(GBoxGame active_game) {
    this->active_game = active_game;
}

static void load_style_context() {
    GtkCssProvider *css_prov = gtk_css_provider_new();

    gtk_css_provider_load_from_data(css_prov, CSS_DATA, -1, NULL);

    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(css_prov),
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

static void start_game_button_clicked(GtkWidget *button, GBoxWindow *win) {
    const gchar *title_game;
    gint size_x, size_y;

    GtkWidget *visible_child = win->get_stack_game();
    GtkWindow *window = GTK_WINDOW(win->get_gbox_window());
    GtkStack *stack_main = GTK_STACK(win->get_stack_main());
    GtkStack *stack_game = GTK_STACK(win->get_stack_game());
    gboolean resizable = TRUE;

    /* Change the active game */
    win->set_active_game(win->get_active_game());

    switch (win->get_active_game()) {
    case GBOX_GAME_TTT:
        win->get_view_ttt()->reset();
        title_game = GBOX_TITLE_GAME_TTT;
        size_x = GBOX_SIZE_TTT_X;
        size_y = GBOX_SIZE_TTT_Y;
        break;
    case GBOX_GAME_CF:
        win->get_view_cf()->reset();
        title_game = GBOX_TITLE_GAME_CF;
        size_x = GBOX_SIZE_CF_X;
        size_y = GBOX_SIZE_CF_Y;
        break;
    case GBOX_GAME_MILL:
        win->get_view_mill()->reset();
        title_game = GBOX_TITLE_GAME_MILL;
        resizable = FALSE;
        size_x = GBOX_SIZE_MILL_X;
        size_y = GBOX_SIZE_MILL_Y;
        break;
    case GBOX_GAME_CHKS:
        win->get_view_chks()->reset();
        title_game = GBOX_TITLE_GAME_CHKS;
        resizable = FALSE;
        size_x = GBOX_SIZE_CHKS_X;
        size_y = GBOX_SIZE_CHKS_Y;
        break;
    }

    /* Hide preview stack in order to resize the window properly */
    gtk_widget_hide(win->get_stack_prev());

    /* Resize window properly */
    gtk_stack_set_visible_child_name(stack_game, title_game);
    gtk_stack_set_visible_child(stack_main, visible_child);
    gtk_window_set_default_size(window, size_x, size_y);
    gtk_window_resize(window, size_x, size_y);
    gdk_display_flush(gdk_display_get_default());
    gtk_window_set_resizable(window, resizable);

    /* Make header bar buttons sensitive */
    gtk_widget_set_sensitive(win->get_btn_back(), TRUE);
    gtk_widget_set_sensitive(win->get_btn_new(), TRUE);
}

static void new_game_button_clicked(GtkWidget *button, GBoxWindow *win) {
    /* Reset game */
    switch (win->get_active_game()) {
    case GBOX_GAME_TTT:
        win->get_view_ttt()->reset();
        break;
    case GBOX_GAME_CF:
        win->get_view_cf()->reset();
        break;
    case GBOX_GAME_MILL:
        win->get_view_mill()->reset();
        break;
    case GBOX_GAME_CHKS:
        win->get_view_chks()->reset();
        break;
    }
}

static void back_button_clicked(GtkWidget *button, GBoxWindow *win) {
    GtkWindow *window = GTK_WINDOW(win->get_gbox_window());
    GtkHeaderBar *hbar = GTK_HEADER_BAR(win->get_hbar());
    GtkStack *stack_main = GTK_STACK(win->get_stack_main());
    gboolean resizable = gtk_window_get_resizable(window);

    /* Reset the current game by pretending the new game button was clicked */
    new_game_button_clicked(NULL, win);

    /* Show preview stack again */
    gtk_widget_show(win->get_stack_prev());

    if (!resizable) gtk_window_set_resizable(window, TRUE);

    gtk_window_set_default_size(window, GBOX_SIZE_WIN_X, GBOX_SIZE_WIN_Y);
    gtk_window_resize(window, GBOX_SIZE_WIN_X, GBOX_SIZE_WIN_Y);
    gtk_stack_set_visible_child(stack_main, win->get_grid_main());

    /* Change header bar title */
    gtk_header_bar_set_title(hbar, GBOX_TITLE_MAIN);

    /* Turn sensitivity of header bar buttons off */
    gtk_widget_set_sensitive(win->get_btn_back(), FALSE);
    gtk_widget_set_sensitive(win->get_btn_new(), FALSE);
}

void GBoxWindow::gbox_window_add_interface() {
    GtkStack *stack_prev = GTK_STACK(this->stack_prev);
    GtkStack *stack_game = GTK_STACK(this->stack_game);

    const gchar *title_prev[GAME_NUM] = {
        GBOX_TITLE_PREV_TTT,
        GBOX_TITLE_PREV_CF,
        GBOX_TITLE_PREV_MILL,
        GBOX_TITLE_PREV_CHKS,
    };

    const gchar *title_game[GAME_NUM] = {
        GBOX_TITLE_GAME_TTT,
        GBOX_TITLE_GAME_CF,
        GBOX_TITLE_GAME_MILL,
        GBOX_TITLE_GAME_CHKS,
    };

    const gchar *image_name[GAME_NUM] = {
        "tictactoe-preview.png",
        "connect-four-preview.png",
        "mill-preview.png",
        "checkers-preview.png",
    };

    GtkWidget *view_prev[GAME_NUM] = {
        this->prev_ttt->get_viewport(),
        this->prev_cf->get_viewport(),
        this->prev_mill->get_viewport(),
        this->prev_chks->get_viewport(),
    };

    GtkWidget *view_game[GAME_NUM] = {
        this->view_ttt->get_viewport(),
        this->view_cf->get_viewport(),
        this->view_mill->get_viewport(),
        this->view_chks->get_viewport(),
    };

    GBoxPreview *preview[GAME_NUM] = {
        this->prev_ttt,
        this->prev_cf,
        this->prev_mill,
        this->prev_chks,
    };

    for (gint i = 0; i < GAME_NUM; ++i) {
        gtk_stack_add_titled(stack_prev, view_prev[i], title_prev[i], title_prev[i]);
        gtk_stack_add_titled(stack_game, view_game[i], title_game[i], title_game[i]);

        preview[i]->set_title(title_prev[i]);
        preview[i]->set_image_name(image_name[i]);

        GtkWidget *button = preview[i]->get_start_button();
        g_signal_connect(button, "clicked", G_CALLBACK(start_game_button_clicked), this);
    }

    /* Connect header bar to games */
    this->view_ttt->set_header_bar(this->hbar);
    this->view_cf->set_header_bar(this->hbar);
    this->view_mill->set_header_bar(this->hbar);
    this->view_chks->set_header_bar(this->hbar);
}

TttView *GBoxWindow::get_view_ttt() {
    return this->view_ttt;
}

CfView *GBoxWindow::get_view_cf() {
    return this->view_cf;
}

MillView *GBoxWindow::get_view_mill() {
    return this->view_mill;
}

ChksView *GBoxWindow::get_view_chks() {
    return this->view_chks;
}

GtkWidget *GBoxWindow::get_stack_main() {
    return this->stack_main;
}

GtkWidget *GBoxWindow::get_stack_prev() {
    return this->stack_prev;
}

GtkWidget *GBoxWindow::get_stack_game() {
    return this->stack_game;
}


GtkWidget *GBoxWindow::get_btn_back() {
    return this->btn_back;
}

GtkWidget *GBoxWindow::get_btn_new() {
    return this->btn_new;
}

GtkWidget *GBoxWindow::get_hbar() {
    return this->hbar;
}

GtkWidget *GBoxWindow::get_grid_main() {
    return this->grid_main;
}

GtkWidget *GBoxWindow::get_gbox_window() {
	return this->self;
}

void GBoxWindow::set_main_window() {
    /* Window */
    gtk_container_add(GTK_CONTAINER(this->self), this->stack_main);

    /* Header bar */
    gtk_header_bar_pack_start(GTK_HEADER_BAR(this->hbar), this->btn_back);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(this->hbar), this->btn_new);

    /* Main grid */
    gtk_grid_attach(GTK_GRID(this->grid_main), this->sidebar,    0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(this->grid_main), this->stack_prev, 1, 0, 1, 1);

    /* Sidebar */
    gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR(this->sidebar), GTK_STACK(this->stack_prev));
    gtk_widget_set_size_request(this->sidebar, 180, -1);
    gtk_widget_set_vexpand(this->sidebar, TRUE);

    /* Main stack */
    gtk_stack_add_titled(GTK_STACK(this->stack_main), this->grid_main, "Prev", "Prev");
    gtk_stack_add_titled(GTK_STACK(this->stack_main), this->stack_game, "Game", "Game");

    /* Preview stack */
    gtk_stack_set_transition_type(GTK_STACK(this->stack_prev), GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);
    gtk_stack_set_transition_duration(GTK_STACK(this->stack_prev), 500);
    gtk_widget_set_vexpand(this->stack_prev, TRUE);
    gtk_widget_set_hexpand(this->stack_prev, TRUE);

    /* Back button */
    g_signal_connect(this->btn_back, "clicked", G_CALLBACK(back_button_clicked), this);
    gtk_widget_set_sensitive(this->btn_back, FALSE);
    gtk_button_set_image(GTK_BUTTON(this->btn_back),
                         gtk_image_new_from_icon_name(
                         "go-previous-symbolic",
                         GTK_ICON_SIZE_BUTTON));

    /* New game button */
    g_signal_connect(this->btn_new, "clicked", G_CALLBACK(new_game_button_clicked), this);
    gtk_widget_set_sensitive(this->btn_new, FALSE);
    gtk_style_context_add_class(gtk_widget_get_style_context(this->btn_new), "suggested-action");
}

void GBoxWindow::del_start_window() {
    gtk_widget_destroy(this->box_start);
}

static void on_start_button_clicked(GtkButton* button, GBoxWindow *win) {
    win->del_start_window();
    win->set_main_window();
    gtk_widget_show_all(win->get_gbox_window());
}

GBoxWindow::GBoxWindow() {
    this->self       = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    this->hbar       = gtk_header_bar_new();
    this->grid_main  = gtk_grid_new();
    this->box_start  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    this->sidebar    = gtk_stack_sidebar_new();

    this->stack_main = gtk_stack_new();
    this->stack_prev = gtk_stack_new();
    this->stack_game = gtk_stack_new();

    this->btn_back = gtk_button_new();
    this->btn_new  = gtk_button_new_with_label("New Game");

    this->prev_ttt  = new GBoxPreview();
    this->prev_cf   = new GBoxPreview();
    this->prev_mill = new GBoxPreview();
    this->prev_chks = new GBoxPreview();

    this->view_ttt  = new TttView();
    this->view_cf   = new CfView();
    this->view_mill = new MillView();
    this->view_chks = new ChksView();

    /* Window */
    gtk_style_context_add_class(gtk_widget_get_style_context(this->self), GBOX_CLASS_WINDOW);
    gtk_window_set_default_size(GTK_WINDOW(this->self), GBOX_SIZE_WIN_X, GBOX_SIZE_WIN_Y);
    gtk_window_set_titlebar(GTK_WINDOW(this->self), this->hbar);
    gtk_window_set_position(GTK_WINDOW(this->self), GTK_WIN_POS_CENTER);
    this->gbox_window_add_interface();
    gtk_container_add(GTK_CONTAINER(this->self), this->box_start);
    g_signal_connect(this->self, "delete-event", gtk_main_quit, this);

    /* Header bar */
    gtk_header_bar_set_title(GTK_HEADER_BAR(this->hbar), GBOX_TITLE_MAIN);
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(this->hbar), TRUE);

    /* Start grid */
    GtkWidget *title_label = gtk_label_new("Yee's FunGames");
    gtk_style_context_add_class(gtk_widget_get_style_context(title_label), GBOX_TITLE_START);

    GtkWidget *menu_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    GtkWidget *help_button = gtk_button_new_with_label("Help");
    GtkWidget *start_button = gtk_button_new_with_label("Start");
    GtkWidget *setting_button = gtk_button_new_with_label("Setting");

    gtk_box_pack_start(GTK_BOX(menu_box), help_button, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(menu_box), start_button, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(menu_box), setting_button, TRUE, FALSE, 0);

    g_signal_connect(G_OBJECT(start_button), "clicked", G_CALLBACK(on_start_button_clicked), this);

    gtk_box_pack_start(GTK_BOX(this->box_start), title_label, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(this->box_start), menu_box, TRUE, FALSE, 10);

    load_style_context();
}