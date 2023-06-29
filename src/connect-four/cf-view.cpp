#include "cf-field.h"
#include "cf-check.h"
#include "cf-view.h"

static void cf_field_leave(GtkWidget *button, CfField *field) {
    CfView *view = field->get_view();

    if (!view->get_running()) return;

    field->set_preowner(CF_OWNER_NONE);
}

static void cf_field_enter(GtkWidget *button, CfField *field) {
    CfView *view = field->get_view();
    CfOwner owner = (view->get_round() % 2 == 0) ? CF_OWNER_ONE : CF_OWNER_TWO;

    if (!view->get_running()) return;

    field->set_preowner(owner);
}

static void cf_field_clicked(GtkWidget *button, CfField *field) {
    CfView *view = field->get_view();
    CfField *lowest = cf_check_get_lowest_field(view->get_field(), field);
    GtkHeaderBar *hbar = GTK_HEADER_BAR(view->get_header_bar());
    CfOwner owner = field->get_owner();
    CfOwner enemy = (view->get_round() % 2 == 0) ? CF_OWNER_TWO : CF_OWNER_ONE;
    CfOwner owner_now = (view->get_round() % 2 == 0) ? CF_OWNER_ONE : CF_OWNER_TWO;

    /* Check if game is running */
    if (!view->get_running()) return;

    /* Check if field is assigned */
    if (owner != CF_OWNER_NONE) return;

    /* Check if column has no free fields */
    if (!lowest) return;

    /* Assign owner to player */
    lowest->set_owner(owner_now);

    /* Swap preowner from initial field */
    field->set_preowner(enemy);

    /* Check if someone has won */
    if (cf_check_get_won(view->get_field())) {
        if (view->get_round() % 2 == 0) {
            gtk_header_bar_set_title(hbar, CF_TITLE_WON_ONE);
        } else {
            gtk_header_bar_set_title(hbar, CF_TITLE_WON_TWO);
        }

        field->set_preowner(CF_OWNER_NONE);

        view->set_running(FALSE);
        return;
    }

    /* Check for a draw */
    if (view->get_round() == 41) {
        gtk_header_bar_set_title(hbar, CF_TITLE_DRAW);
        view->set_running(FALSE);
        return;
    }

    /* Switch owner */
    if (view->get_round() % 2 == 0) {
        gtk_header_bar_set_title(hbar, CF_TITLE_TURN_TWO);
    } else {
        gtk_header_bar_set_title(hbar, CF_TITLE_TURN_ONE);
    }

    view->set_round(view->get_round() + 1);
}

CfField *(*CfView::get_field())[CF_ROW_SIZE] {
    return this->field;
}

void CfView::reset() {
    this->running = TRUE;
    GtkHeaderBar *hbar = GTK_HEADER_BAR(this->hbar);

    for (gint i = 0; i < CF_COL_SIZE; ++i) {
        for (gint j = 0; j < CF_ROW_SIZE; ++j) {
            GtkWidget *widget = this->field[i][j]->get_button();
            GtkWidget *label  = gtk_bin_get_child(GTK_BIN(widget));
            this->field[i][j]->set_owner(CF_OWNER_NONE);
            gtk_label_set_markup(GTK_LABEL(label), "");
        }
    }

    gtk_header_bar_set_title(hbar, CF_TITLE_TURN_ONE);
    this->round = 0;
}

GtkWidget *CfView::get_viewport() {
    return this->grid;
}

gboolean CfView::get_running() {
    return this->running;
}

void CfView::set_running(gboolean running) {
    this->running = running;
}

gint CfView::get_round() {
    return this->round;
}

void CfView::set_round(gint round) {
    this->round = round;
}

GtkWidget *CfView::get_header_bar() {
    return this->hbar;
}

void CfView::set_header_bar(GtkWidget *hbar) {
    this->hbar = hbar;
}

CfView::CfView() {
    this->grid    = gtk_grid_new();
    this->hbar    = NULL;
    this->running = TRUE;
    this->round   = 0;

    /* Grid */
    GtkStyleContext *context = gtk_widget_get_style_context(this->grid);
    gtk_style_context_add_class(context, CF_CLASS_GRID);
    gtk_grid_set_column_homogeneous(GTK_GRID(this->grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(this->grid), TRUE);
    
    GtkGrid *grid = GTK_GRID(this->grid);

    for (gint i = 0; i < CF_COL_SIZE; ++i) {
        for (gint j = 0; j < CF_ROW_SIZE; ++j) {
            field[i][j] = new CfField(i, j);
            GtkWidget *button = field[i][j]->get_button();
            field[i][j]->set_view(this);
            g_signal_connect(button, "clicked", G_CALLBACK(cf_field_clicked), field[i][j]);
            g_signal_connect(button, "enter",   G_CALLBACK(cf_field_enter),   field[i][j]);
            g_signal_connect(button, "leave",   G_CALLBACK(cf_field_leave),   field[i][j]);
            gtk_grid_attach(grid, button, i, j, 1, 1);
        }
    }
}