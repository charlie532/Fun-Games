#include "ttt-check.h"
#include "ttt-view.h"
#include "ttt-field.h"

static void ttt_field_enter(GtkWidget *button, TttField *field) {
    TttView *view = field->get_view();
    TttOwner owner = field->get_owner();
    TttOwner owner_now = (view->get_round() % 2 == 0) ? TTT_OWNER_ONE : TTT_OWNER_TWO;

    if (!view->get_running()) return;

    if (owner != TTT_OWNER_NONE) return;

    field->set_preowner(owner_now);
}

static void ttt_field_leave(GtkWidget *button, TttField *field) {
    TttView *view = field->get_view();
    TttOwner owner = field->get_owner();

    if (!view->get_running()) return;

    if (owner != TTT_OWNER_NONE) return;

    field->set_preowner(TTT_OWNER_NONE);
}

static void ttt_field_clicked(GtkWidget *button, TttField *field) {
    TttView *view = field->get_view();
    GtkHeaderBar *hbar = GTK_HEADER_BAR(view->get_hbar());
    TttOwner owner = field->get_owner();
    TttOwner owner_now = (view->get_round() % 2 == 0) ? TTT_OWNER_ONE : TTT_OWNER_TWO;

    /* Check if game is running */
    if (!view->get_running()) return;

    /* Check if field is assigned already */
    if (owner != TTT_OWNER_NONE) return;

    /* Assign owner to field */
    field->set_owner(owner_now);

    /* Check for win */
    if (ttt_check_get_won(view->get_field())) {
        if (view->get_round() % 2 == 0) {
            gtk_header_bar_set_title(hbar, TTT_TITLE_WON_ONE);
        } else {
            gtk_header_bar_set_title(hbar, TTT_TITLE_WON_TWO);
        }

        view->set_running(FALSE);
        return;
    }

    /* Check for draw */
    if (view->get_round() == 8) {
        gtk_header_bar_set_title(hbar, TTT_TITLE_DRAW);
        return;
    }

    /* End turn */
    if (view->get_round() % 2 == 0) {
        gtk_header_bar_set_title(hbar, TTT_TITLE_TURN_TWO);
    } else {
        gtk_header_bar_set_title(hbar, TTT_TITLE_TURN_ONE);
    }

    view->set_round(view->get_round() + 1);
}

void TttView::reset() {
    GtkHeaderBar *hbar = GTK_HEADER_BAR(this->hbar);
    this->running = TRUE;

    for (gint i = 0; i < TTT_SIZE; ++i) {
        for (gint j = 0; j < TTT_SIZE; ++j) {
            field[i][j]->set_owner(TTT_OWNER_NONE);
        }
    }

    gtk_header_bar_set_title(hbar, TTT_TITLE_TURN_ONE);
    this->round = 0;
}

gint TttView::get_round() {
    return this->round;
}

void TttView::set_round(gint round) {
    this->round = round;
}

gboolean TttView::get_running() {
    return this->running;
}

void TttView::set_running(gboolean running) {
    this->running = running;
}

TttField *(*TttView::get_field())[TTT_SIZE]{
    return this->field;
}

GtkWidget *TttView::get_hbar() {
    return this->hbar;
}

GtkWidget *TttView::get_viewport() {
    return this->grid;
}

void TttView::set_header_bar(GtkWidget *hbar) {
    this->hbar = hbar;
}

TttView::TttView() {
    this->grid    = gtk_grid_new();
    this->hbar    = NULL;
    this->running = TRUE;
    this->round   = 0;

    /* Grid */
    gtk_grid_set_column_homogeneous(GTK_GRID(this->grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(this->grid), TRUE);
    
    GtkGrid *grid = GTK_GRID(this->grid);

    for (gint i = 0; i < TTT_SIZE; ++i) {
        for (gint j = 0; j < TTT_SIZE; ++j) {
            this->field[i][j] = new TttField();
            GtkWidget *button = field[i][j]->get_button();
            field[i][j]->set_view(this);
            g_signal_connect(button, "clicked", G_CALLBACK(ttt_field_clicked), field[i][j]);
            g_signal_connect(button, "enter",   G_CALLBACK(ttt_field_enter),   field[i][j]);
            g_signal_connect(button, "leave",   G_CALLBACK(ttt_field_leave),   field[i][j]);
            gtk_grid_attach(grid, button, i, j, 1, 1);
        }
    }
}
