#include "chks-view.h"
#include "chks-field.h"

GtkWidget *ChksField::get_button() {
	return this->button;
}

ChksView *ChksField::get_view() {
	return this->view;
}

void ChksField::set_view(ChksView *view) {
	this->view = view;
}

ChksOwner ChksField::get_owner() {
	return this->owner;
}

void ChksField::set_owner(ChksOwner owner) {
	this->owner = owner;

	GtkStyleContext *context = gtk_widget_get_style_context(this->button);

	switch (owner) {
	case CHKS_OWNER_NONE:
		gtk_style_context_remove_class(context, CHKS_CLASS_ONE);
		gtk_style_context_remove_class(context, CHKS_CLASS_TWO);
		break;
	case CHKS_OWNER_ONE:
		gtk_style_context_remove_class(context, CHKS_CLASS_ONE_PRE);
		gtk_style_context_add_class(context, CHKS_CLASS_ONE);
		break;
	case CHKS_OWNER_TWO:
		gtk_style_context_remove_class(context, CHKS_CLASS_TWO_PRE);
		gtk_style_context_add_class(context, CHKS_CLASS_TWO);
		break;
	}
}

ChksOwner ChksField::get_initial_owner() {
	static gint white_x[3][4] = {
		{0, 2, 4, 6}, {1, 3, 5, 7}, {0, 2, 4, 6},
	};

	static gint white_y[3][4] = {
		{7, 7, 7, 7}, {6, 6, 6, 6}, {5, 5, 5, 5},
	};

	static gint black_x[3][4] = {
		{1, 3, 5, 7}, {0, 2, 4, 6}, {1, 3, 5, 7},
	};

	static gint black_y[3][4] = {
		{0, 0, 0, 0}, {1, 1, 1, 1}, {2, 2, 2, 2},
	};

	for (gint i = 0; i < 3; ++i) {
		for (gint j = 0; j < 4; ++j) {
			if (this->col == white_x[i][j] && this->row == white_y[i][j]) return CHKS_OWNER_ONE;
			if (this->col == black_x[i][j] && this->row == black_y[i][j]) return CHKS_OWNER_TWO;
		}
	}

	return CHKS_OWNER_NONE;
}

gboolean ChksField::get_is_queen() {
	return this->is_queen;
}

void ChksField::set_preowner(ChksOwner owner) {
	GtkStyleContext *context = gtk_widget_get_style_context(this->button);

	switch (owner) {
	case CHKS_OWNER_NONE:
		gtk_style_context_remove_class(context, CHKS_CLASS_ONE_PRE);
		gtk_style_context_remove_class(context, CHKS_CLASS_TWO_PRE);
		break;
	case CHKS_OWNER_ONE:
		gtk_style_context_add_class(context, CHKS_CLASS_ONE_PRE);
		break;
	case CHKS_OWNER_TWO:
		gtk_style_context_add_class(context, CHKS_CLASS_TWO_PRE);
		break;
	}
}

void ChksField::set_is_queen(gboolean is_queen) {
	this->is_queen = is_queen;
}

gint ChksField::get_col() {
	return this->col;
}

gint ChksField::get_row() {
	return this->row;
}

ChksField::ChksField(gint col, gint row) {
	this->col = col;
	this->row = row;

	this->button   = gtk_button_new();
	this->view     = NULL;
	this->owner    = this->get_initial_owner();
	this->is_queen = FALSE;

	/* Add style to button */
	gtk_container_set_border_width(GTK_CONTAINER(this->button), CHKS_SIZE);
	GtkStyleContext *context = gtk_widget_get_style_context(this->button);
	gtk_style_context_add_class(context, CHKS_CLASS_FIELD);

	switch (this->owner) {
	case CHKS_OWNER_NONE:
		break;
	case CHKS_OWNER_ONE:
		gtk_style_context_add_class(context, CHKS_CLASS_ONE);
		break;
	case CHKS_OWNER_TWO:
		gtk_style_context_add_class(context, CHKS_CLASS_TWO);
		break;
	}
}