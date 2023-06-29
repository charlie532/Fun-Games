#ifndef __TTT_FIELD_H__
#define __TTT_FIELD_H__

#include <gtk/gtk.h>

#define TTT_MARKUP_ONE "<span size='47500' color='#000000'>X</span>"
#define TTT_MARKUP_TWO "<span size='47500' color='#000000'>O</span>"

#define TTT_PRE_MARKUP_ONE "<span size='47500' color='#858585'>X</span>"
#define TTT_PRE_MARKUP_TWO "<span size='47500' color='#858585'>O</span>"

#define TTT_CLASS_FIELD "ttt-field"

typedef enum {
    TTT_OWNER_NONE,
    TTT_OWNER_ONE,
    TTT_OWNER_TWO,
} TttOwner;

class TttView;

class TttField {
private:
    /* Widgets */
    GtkWidget *button;
    GtkWidget *label;

    /* Connection to view */
    TttView *view;

    /* States */
    TttOwner owner;

public:
    GtkWidget *get_button();
    TttView *get_view();
    void set_view(TttView *);
    TttOwner get_owner();
    void set_owner(TttOwner);
    void set_preowner(TttOwner);
    TttField();
};

#endif /* __TTT_FIELD_H__ */
