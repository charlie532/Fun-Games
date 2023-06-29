#include "mill-check.h"
#include "mill-field.h"
#include "mill-view.h"

static void mill_field_enter(GtkWidget *button, MillField *piece) {
    MillView *view = piece->get_view();
    MillOwner owner = piece->get_owner();
    MillOwner owner_now = (view->get_round() % 2 == 0) ? MILL_OWNER_ONE : MILL_OWNER_TWO;
    gint pieces_left = (view->get_round() % 2 == 0) ? view->get_piece_one() : view->get_piece_two();
    gboolean can_jump = (pieces_left > 3) ? FALSE : TRUE;
    MillStatus st = view->get_status();

    if (owner != MILL_OWNER_NONE || st == MILL_STATUS_DONE || st == MILL_STATUS_TAKE) return;

    if (st == MILL_STATUS_MOVE) {
        if (!view->get_last()) return;

        gboolean in_range = mill_check_get_field_in_range(view->get_field(), view->get_last(), piece);

        if (!in_range && !can_jump) return;
    }

    piece->set_preowner(owner_now);
}

static void mill_field_leave(GtkWidget *button, MillField *piece) {
    MillView *view = piece->get_view();
    MillOwner owner = piece->get_owner();
    MillStatus st = view->get_status();

    if (owner != MILL_OWNER_NONE || st == MILL_STATUS_DONE || st == MILL_STATUS_TAKE) return;

    piece->set_preowner(MILL_OWNER_NONE);
}

void MillView::set_status(MillStatus status) {
    this->status = status;

    GtkHeaderBar *hbar = GTK_HEADER_BAR(this->hbar);
    const gchar *title;

    switch (status) {
    case MILL_STATUS_PLACE:
        title = (this->round % 2 == 0) ? MILL_TITLE_PLACE_ONE : MILL_TITLE_PLACE_TWO;
        break;
    case MILL_STATUS_MOVE:
        title = (this->round % 2 == 0) ? MILL_TITLE_MOVE_ONE : MILL_TITLE_MOVE_TWO;
        break;
    case MILL_STATUS_TAKE:
        title = (this->round % 2 == 0) ? MILL_TITLE_TAKE_ONE : MILL_TITLE_TAKE_TWO;
        break;
    case MILL_STATUS_DONE:
        title = (this->round % 2 == 0) ? MILL_TITLE_WON_ONE : MILL_TITLE_WON_TWO;
        break;
    }

    gtk_header_bar_set_title(hbar, title);
}

void MillView::take(MillField *piece) {
    MillOwner owner = piece->get_owner();
    MillOwner enemy = (this->round % 2 == 0) ? MILL_OWNER_TWO : MILL_OWNER_ONE;
    gint free_fields = mill_check_get_free_fields(this->field, enemy);
    gint in_mill = mill_check_get_field_in_mill(this->field, piece);

    /* Check if the piece belongs to the enemy */
    if (owner != enemy) return;

    /* Check if fields in in mill */
    if (in_mill > 0 && free_fields > 0) return;

    piece->set_owner(MILL_OWNER_NONE);

    gint pieces_left = (this->round % 2 == 0) ? --this->pieces_two : --this->pieces_one;

    /* Check for win */
    if (pieces_left < 3) {
        this->set_status(MILL_STATUS_DONE);
        return;
    }

    /* Check if two mills have been closed */
    if (--this->mill_cnt > 0) return;

    if (++this->round > 17) {
        this->set_status(MILL_STATUS_MOVE);
    } else {
        this->set_status(MILL_STATUS_PLACE);
    }
}

void MillView::move(MillField *piece) {
    gint pieces_left = (this->round % 2 == 0) ? this->pieces_one : this->pieces_two;
    MillOwner owner = piece->get_owner();
    MillOwner owner_now = (this->round % 2 == 0) ? MILL_OWNER_ONE : MILL_OWNER_TWO;

    /* Check the field to move */
    if (owner == owner_now) {
        this->last = piece;
        return;
    }

    /* Check if field to move is selected */
    if (!this->last) return;

    /* Check destination field */
    if (owner != MILL_OWNER_NONE) return;

    /* Check if destination is out of range */
    gboolean in_range = mill_check_get_field_in_range(this->field, this->last, piece);
    if (!in_range && pieces_left > 3) return;

    /* Move field */
    this->last->set_owner(MILL_OWNER_NONE);
    piece->set_owner(owner_now);
    this->last = NULL;

    /* Check mill count */
    this->mill_cnt = mill_check_get_field_in_mill(this->field, piece);

    if (this->mill_cnt > 0) {
        this->set_status(MILL_STATUS_TAKE);
        return;
    }

    this->round++;
    this->set_status(MILL_STATUS_MOVE);
}

void MillView::place(MillField *piece) {
    MillOwner owner, owner_now;

    owner = piece->get_owner();
    owner_now = (this->round % 2 == 0) ? MILL_OWNER_ONE : MILL_OWNER_TWO;

    /* Check if field is assigned */
    if (owner != MILL_OWNER_NONE) return;

    /* Assign owner to field */
    piece->set_owner(owner_now);

    /* Check mill count */
    this->mill_cnt = mill_check_get_field_in_mill(this->field, piece);

    if (this->mill_cnt > 0) {
        this->set_status(MILL_STATUS_TAKE);
        return;
    }

    /* Check if all pieces were placed */
    if (++this->round == 18) {
        this->set_status(MILL_STATUS_MOVE);
    } else {
        this->set_status(MILL_STATUS_PLACE);
    }
}

static void mill_field_clicked(GtkWidget *button, MillField *piece) {
    MillView *view = piece->get_view();

    switch (view->get_status()) {
    case MILL_STATUS_PLACE:
        view->place(piece);
        break;
    case MILL_STATUS_MOVE:
        view->move(piece);
        break;
    case MILL_STATUS_TAKE:
        view->take(piece);
        break;
    case MILL_STATUS_DONE:
        return;
    }
}

void MillView::reset() {
    MillOwner owner;

    for (gint i = 0; i < MILL_SIZE; ++i) {
        for (gint j = 0; j < MILL_SIZE; ++j) {
            owner = this->field[i][j]->get_owner();

            if (owner == MILL_OWNER_BLOCK) continue;

            this->field[i][j]->set_owner(MILL_OWNER_NONE);
        }
    }

    this->round = 0;
    this->pieces_one = 9;
    this->pieces_two = 9;

    this->set_status(MILL_STATUS_PLACE);
}

gint MillView::get_piece_one() {
    return this->pieces_one;
}

gint MillView::get_piece_two() {
    return this->pieces_two;
}

MillField *(*MillView::get_field())[MILL_SIZE] {
    return this->field;
}

MillField *MillView::get_last() {
    return this->last;
}

gint MillView::get_round() {
    return this->round;
}

MillStatus MillView::get_status() {
    return this->status;
}

GtkWidget *MillView::get_viewport() {
    return this->grid;
}

void MillView::set_header_bar(GtkWidget *hbar) {
    this->hbar = hbar;
}

MillView::MillView() {
    this->grid = gtk_grid_new();
    this->hbar = NULL;
    this->last = NULL;
    this->status = MILL_STATUS_PLACE;
    this->round = 0;
    this->mill_cnt = 0;
    this->pieces_one = 9;
    this->pieces_two = 9;

    /* Grid */
    GtkStyleContext *context = gtk_widget_get_style_context(this->grid);
    gtk_style_context_add_class(context, MILL_CLASS_GRID);
    gtk_grid_set_column_homogeneous(GTK_GRID(this->grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(this->grid), TRUE);
    
    GtkGrid *grid = GTK_GRID(this->grid);

    for (gint i = 0; i < MILL_SIZE; ++i) {
        for (gint j = 0; j < MILL_SIZE; ++j) {
            this->field[i][j] = new MillField(i, j);
            MillOwner owner = this->field[i][j]->get_owner();
            if (owner == MILL_OWNER_BLOCK) continue;
            this->field[i][j]->set_view(this);
            GtkWidget *button = this->field[i][j]->get_button();
            g_signal_connect(button, "clicked", G_CALLBACK(mill_field_clicked), this->field[i][j]);
            g_signal_connect(button, "enter", G_CALLBACK(mill_field_enter), this->field[i][j]);
            g_signal_connect(button, "leave", G_CALLBACK(mill_field_leave), this->field[i][j]);
            gtk_grid_attach(grid, button, i, j, 1, 1);
        }
    }
}
