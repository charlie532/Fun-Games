#ifndef __CF_FIELD_H__
#define __CF_FIELD_H__

#include <gtk/gtk.h>

#define CF_CLASS_FIELD "cf-field"

#define CF_CLASS_ONE "cf-player-one"
#define CF_CLASS_TWO "cf-player-two"

typedef enum {
    CF_OWNER_NONE,
    CF_OWNER_ONE,
    CF_OWNER_TWO,
} CfOwner;

class CfView;

class CfField {
private:
    /* Widget */
    GtkWidget *button;

    /* Connection to view */
    CfView *view;

    /* States */
    CfOwner owner;
    gint col;
    gint row;
public:
    GtkWidget *get_button();
    CfView *get_view();
    void set_view(CfView *);
    CfOwner get_owner();
    void set_owner(CfOwner);
    void set_preowner(CfOwner);
    gint get_col();
    gint get_row();
    CfField(gint, gint);
};

#endif /* __CF_FIELD_H__ */