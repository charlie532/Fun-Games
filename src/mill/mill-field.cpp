#include "mill-view.h"
#include "mill-field.h"

MillOwner MillField::get_initial_owner() {
    gint col = this->col, row = this->row;

    gint block_x[6][4] = {
        {1, 2, 4, 5}, {0, 2, 4, 6}, {0, 1, 5, 6},
        {0, 1, 5, 6}, {0, 2, 4, 6}, {1, 2, 4, 5},
    };

    gint block_y[6][4] = {
        {0, 0, 0, 0}, {1, 1, 1, 1}, {2, 2, 2, 2},
        {4, 4, 4, 4}, {5, 5, 5, 5}, {6, 6, 6, 6},
    };

    /* Middle piece exception */
    if (col == 3 && row == 3) return MILL_OWNER_BLOCK;

    for (gint i = 0; i < 6; ++i) {
        for (gint j = 0; j < 4; ++j) {
            if (col == block_x[i][j] && row == block_y[i][j]) return MILL_OWNER_BLOCK;
        }
    }

    return MILL_OWNER_NONE;
}

GtkWidget *MillField::get_button() {
    return this->button;
}

MillView *MillField::get_view() {
    return this->view;
}

void MillField::set_view(MillView *view) {
    this->view = view;
}

MillOwner MillField::get_owner() {
    return this->owner;
}

void MillField::set_owner(MillOwner owner) {
    this->owner = owner;
    GtkStyleContext *context = gtk_widget_get_style_context(this->button);

    switch (owner) {
    case MILL_OWNER_NONE:
        gtk_style_context_remove_class(context, MILL_CLASS_ONE);
        gtk_style_context_remove_class(context, MILL_CLASS_TWO);
        break;
    case MILL_OWNER_ONE:
        gtk_style_context_add_class(context, MILL_CLASS_ONE);
        break;
    case MILL_OWNER_TWO:
        gtk_style_context_add_class(context, MILL_CLASS_TWO);
        break;
    default:
        break;
    }
}

void MillField::set_preowner(MillOwner owner) {
    GtkStyleContext *context = gtk_widget_get_style_context(this->button);

    switch (owner) {
    case MILL_OWNER_NONE:
        gtk_style_context_remove_class(context, MILL_CLASS_ONE);
        gtk_style_context_remove_class(context, MILL_CLASS_TWO);
        break;
    case MILL_OWNER_ONE:
        gtk_style_context_add_class(context, MILL_CLASS_ONE);
        break;
    case MILL_OWNER_TWO:
        gtk_style_context_add_class(context, MILL_CLASS_TWO);
        break;
    default:
        break;
    }
}

gint MillField::get_col() {
    return this->col;
}

gint MillField::get_row() {
    return this->row;
}

MillField::MillField(gint col, gint row) {
    this->col = col;
    this->row = row;

    this->view  = NULL;
    this->owner = this->get_initial_owner();

    /* Add style to widget */
    const gchar *class_name;

    if (this->owner == MILL_OWNER_NONE) {
        this->button = gtk_button_new();
        gtk_container_set_border_width(GTK_CONTAINER(this->button), 10);
        class_name = MILL_CLASS_FIELD;
    } else {
        this->button = gtk_label_new(NULL);
        class_name = MILL_CLASS_BLOCK;
    }

    GtkStyleContext *context = gtk_widget_get_style_context(this->button);
    gtk_style_context_add_class(context, class_name);
}
