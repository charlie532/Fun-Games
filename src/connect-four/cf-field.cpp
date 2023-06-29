#include "cf-field.h"
#include "cf-view.h"

GtkWidget *CfField::get_button() {
    return this->button;
}

CfView *CfField::get_view() {
    return this->view;
}

void CfField::set_view(CfView *view) {
    this->view = view;
}

CfOwner CfField::get_owner() {
    return this->owner;
}

void CfField::set_owner(CfOwner owner) {
    this->owner = owner;

    GtkStyleContext *context = gtk_widget_get_style_context(this->button);

    switch (owner) {
    case CF_OWNER_NONE:
        gtk_style_context_remove_class(context, CF_CLASS_ONE);
        gtk_style_context_remove_class(context, CF_CLASS_TWO);
        break;
    case CF_OWNER_ONE:
        gtk_style_context_add_class(context, CF_CLASS_ONE);
        break;
    case CF_OWNER_TWO:
        gtk_style_context_add_class(context, CF_CLASS_TWO);
        break;
    }
}

void CfField::set_preowner(CfOwner owner) {
    if (this->owner != CF_OWNER_NONE) return;

    GtkStyleContext *context = gtk_widget_get_style_context(this->button);

    switch (owner) {
    case CF_OWNER_NONE:
        gtk_style_context_remove_class(context, CF_CLASS_ONE);
        gtk_style_context_remove_class(context, CF_CLASS_TWO);
        break;
    case CF_OWNER_ONE:
        gtk_style_context_remove_class(context, CF_CLASS_TWO);
        gtk_style_context_add_class(context, CF_CLASS_ONE);
        break;
    case CF_OWNER_TWO:
        gtk_style_context_remove_class(context, CF_CLASS_ONE);
        gtk_style_context_add_class(context, CF_CLASS_TWO);
        break;
    }
}

gint CfField::get_col() {
    return this->col;
}

gint CfField::get_row() {
    return this->row;
}

CfField::CfField(gint col, gint row) {
    this->col = col;
    this->row = row;
 
    this->button = gtk_button_new_with_label("");
    this->view   = NULL;
    this->owner  = CF_OWNER_NONE;

    /* Button */
    gtk_container_set_border_width(GTK_CONTAINER(this->button), 10);

    /* Add style to button */
    GtkStyleContext *context = gtk_widget_get_style_context(this->button);
    gtk_style_context_add_class(context, CF_CLASS_FIELD);
}
