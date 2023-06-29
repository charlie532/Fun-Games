#include "ttt-view.h"
#include "ttt-field.h"

GtkWidget *TttField::get_button() {
    return this->button;
}

TttView *TttField::get_view() {
    return this->view;
}

void TttField::set_view(TttView *view) {
    this->view = view;
}

TttOwner TttField::get_owner() {
    return this->owner;
}

void TttField::set_owner(TttOwner owner) {
    this->owner = owner;

    GtkLabel *label;

    label = GTK_LABEL(this->label);

    switch (owner) {
    case TTT_OWNER_NONE:
        gtk_label_set_markup(label, "");
        break;
    case TTT_OWNER_ONE:
        gtk_label_set_markup(label, TTT_MARKUP_ONE);
        break;
    case TTT_OWNER_TWO:
        gtk_label_set_markup(label, TTT_MARKUP_TWO);
        break;
    }
}

void TttField::set_preowner(TttOwner owner) {
    GtkLabel *label;

    label = GTK_LABEL(this->label);

    switch (owner) {
    case TTT_OWNER_NONE:
        gtk_label_set_markup(label, "");
        break;
    case TTT_OWNER_ONE:
        gtk_label_set_markup(label, TTT_PRE_MARKUP_ONE);
        break;
    case TTT_OWNER_TWO:
        gtk_label_set_markup(label, TTT_PRE_MARKUP_TWO);
        break;
    }
}

TttField::TttField() {
    this->button = gtk_button_new_with_label("");
    this->label  = gtk_bin_get_child(GTK_BIN(this->button));
    this->view   = NULL;
    this->owner  = TTT_OWNER_NONE;

    /* Add style to button */
    GtkStyleContext *context = gtk_widget_get_style_context(this->button);
    gtk_style_context_add_class(context, TTT_CLASS_FIELD);
}