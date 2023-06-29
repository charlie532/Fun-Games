#ifndef __MILL_FIELD_H__
#define __MILL_FIELD_H__

#include <gtk/gtk.h>

#define MILL_CLASS_FIELD "mill-field"
#define MILL_CLASS_BLOCK "mill-block"

#define MILL_CLASS_ONE "mill-player-one"
#define MILL_CLASS_TWO "mill-player-two"

typedef enum {
    MILL_OWNER_BLOCK,
    MILL_OWNER_NONE,
    MILL_OWNER_ONE,
    MILL_OWNER_TWO,
} MillOwner;

class MillView;

class MillField {
private:
    /* Widget */
    GtkWidget *button;

    /* Connection to view */
    MillView *view;

    /* States */
    MillOwner owner;
    gint col;
    gint row;

public:
    MillOwner get_initial_owner();
    GtkWidget *get_button();
    MillView *get_view();
    void set_view(MillView *);
    MillOwner get_owner();
    void set_owner(MillOwner);
    void set_preowner(MillOwner);
    gint get_col();
    gint get_row();
    MillField(gint, gint);
};

#endif /* __MILL_FIELD_H__ */