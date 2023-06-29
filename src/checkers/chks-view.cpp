#include "chks-field.h"
#include "chks-check.h"
#include "chks-view.h"

static void chks_field_leave(GtkWidget *button, ChksField *piece) {
	if (piece->get_owner() != CHKS_OWNER_NONE) return;

	piece->set_preowner(CHKS_OWNER_NONE);
}

static void chks_field_enter(GtkWidget *button, ChksField *piece) {
        ChksView *view = piece->get_view();
        ChksOwner owner = piece->get_owner();
        ChksOwner owner_now = (view->get_round() % 2 == 0) ? CHKS_OWNER_ONE : CHKS_OWNER_TWO;

        /* Check if game is running */
        if (view->get_status() == CHKS_STATUS_NONE) return;

        /* Check owner of destination field */
        if (owner != CHKS_OWNER_NONE) return;

        /* Check if field is selected */
        if (!view->get_last()) return;

        ChksTurn turn = chks_check_get_turn(view->get_field(), view->get_last(), piece);

        if (turn == CHKS_TURN_NONE) return;

        piece->set_preowner(owner_now);
}

void ChksView::set_status(ChksStatus status) {
	this->status = status;
	const gchar *title;
	GtkHeaderBar *hbar = GTK_HEADER_BAR(this->hbar);

	switch (status) {
	case CHKS_STATUS_NONE:
		title = (this->round % 2 == 0) ? CHKS_TITLE_WON_ONE : CHKS_TITLE_WON_TWO;
		break;
	case CHKS_STATUS_MOVE:
		title = (this->round % 2 == 0) ? CHKS_TITLE_MOVE_ONE : CHKS_TITLE_MOVE_TWO;
		break;
	case CHKS_STATUS_JUMP_AGAIN:
		title = (this->round % 2 == 0) ? CHKS_TITLE_TAKE_ONE : CHKS_TITLE_TAKE_TWO;
		break;
	}

	gtk_header_bar_set_title(hbar, title);
}

void ChksView::jump(ChksField *piece) {
	ChksOwner owner_now = (this->round % 2 == 0) ? CHKS_OWNER_ONE : CHKS_OWNER_TWO;
	ChksOwner owner_dest = piece->get_owner();
	gint start_x = this->last->get_col();
	gint start_y = this->last->get_row();
	gint dest_x = piece->get_col();
	gint dest_y = piece->get_row();
	gint mid_x = (start_x + dest_x) / 2;
	gint mid_y = (start_y + dest_y) / 2;

	/* Check destination field */
	if (owner_dest != CHKS_OWNER_NONE) return;

	/* Check what turn is intended */
	if (chks_check_get_turn(this->field, this->last, piece) != CHKS_TURN_TAKE) return;

	/* Take away middle piece */
	this->field[mid_x][mid_y]->set_owner(CHKS_OWNER_NONE);

	/* Move pieces */
	this->last->set_owner(CHKS_OWNER_NONE);
	piece->set_owner(owner_now);
	piece->set_is_queen(this->last->get_is_queen());
	this->last->set_is_queen(FALSE);

	/* Check if piece is now queen */
	if (chks_check_get_becomes_queen(piece)) piece->set_is_queen(TRUE);

	/* Substract a piece */
	if (owner_now == CHKS_OWNER_ONE) {
		this->pieces_two--;
	} else {
		this->pieces_one--;
	}

	/* Check if you have to jump again */
	if (chks_check_get_can_jump_again(this->field, piece)) {
		this->last = piece;
		this->set_status(CHKS_STATUS_JUMP_AGAIN);
		return;
	}

	/* Check if someone has won */
	if (this->pieces_one == 0 || this->pieces_two == 0) {
		this->set_status(CHKS_STATUS_NONE);
		return;
	}

	this->last = NULL;
	this->round++;

	this->set_status(CHKS_STATUS_MOVE);
}

void ChksView::move(ChksField *piece) {
	ChksOwner owner = piece->get_owner();
	ChksOwner owner_now = (this->round % 2 == 0) ? CHKS_OWNER_ONE : CHKS_OWNER_TWO;

	if (owner == owner_now) {
		this->last = piece;
		return;
	}

	if (!this->last) return;

	/* Check what turn is intended */
	ChksTurn turn = chks_check_get_turn(this->field, this->last, piece);

	switch (turn) {
	case CHKS_TURN_NONE:
		return;
	case CHKS_TURN_MOVE:
		break;
	case CHKS_TURN_TAKE:
		this->jump(piece);
		return;
	}

	/* Move field */
	this->last->set_owner(CHKS_OWNER_NONE);
	piece->set_owner(owner_now);
	piece->set_is_queen(this->last->get_is_queen());
	this->last->set_is_queen(FALSE);
	this->last = NULL;

	/* Check if piece is now queen */
	if (chks_check_get_becomes_queen(piece)) piece->set_is_queen(TRUE);

	this->round++;

	this->set_status(CHKS_STATUS_MOVE);
}

static void chks_field_clicked(GtkWidget *button, ChksField *piece) {
    ChksView *view = piece->get_view();

    switch (view->get_status()) {
    case CHKS_STATUS_NONE:
        return;
    case CHKS_STATUS_MOVE:
        view->move(piece);
        break;
    case CHKS_STATUS_JUMP_AGAIN:
        view->jump(piece);
        break;
    }
}

void ChksView::reset() {
    for (gint i = 0; i < CHKS_SIZE; ++i) {
        for (gint j = 0; j < CHKS_SIZE; ++j) {
            ChksOwner owner_init = this->field[i][j]->get_initial_owner();
            this->field[i][j]->set_owner(CHKS_OWNER_NONE);
            this->field[i][j]->set_owner(owner_init);
            this->field[i][j]->set_is_queen(FALSE);
        }
    }

    this->last = NULL;
    this->round = 0;
    this->pieces_one = 12;
    this->pieces_two = 12;

    this->set_status(CHKS_STATUS_MOVE);
}

ChksField *(*ChksView::get_field())[CHKS_SIZE] {
	return this->field;
}

ChksField *ChksView::get_last() {
	return this->last;
}

ChksStatus ChksView::get_status() {
    return this->status;
}
gint ChksView::get_round() {
	return this->round;
}

GtkWidget *ChksView::get_viewport() {
    return this->grid;
}

void ChksView::set_header_bar(GtkWidget *hbar) {
    this->hbar = hbar;
}

ChksView::ChksView() {
    this->grid = gtk_grid_new();
    this->hbar = NULL;
    this->last = NULL;
    this->status = CHKS_STATUS_MOVE;
    this->round = 0;
    this->pieces_one = 12;
    this->pieces_two = 12;

    /* Grid */
    GtkStyleContext *context = gtk_widget_get_style_context(this->grid);
    gtk_style_context_add_class(context, CHKS_CLASS_GRID);
    gtk_grid_set_column_homogeneous(GTK_GRID(this->grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(this->grid), TRUE);
    GtkGrid *grid;
    GtkWidget *button;

    grid = GTK_GRID(this->grid);

    for (gint i = 0; i < CHKS_SIZE; ++i) {
        for (gint j = 0; j < CHKS_SIZE; ++j) {
            field[i][j] = new ChksField(i, j);
            button = field[i][j]->get_button();
            field[i][j]->set_view(this);
            gtk_grid_attach(grid, button, i, j, 1, 1);
            g_signal_connect(button, "clicked", G_CALLBACK(chks_field_clicked), field[i][j]);
            g_signal_connect(button, "enter", G_CALLBACK(chks_field_enter), field[i][j]);
            g_signal_connect(button, "leave", G_CALLBACK(chks_field_leave), field[i][j]);
        }
    }
}