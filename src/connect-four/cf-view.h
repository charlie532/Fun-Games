#ifndef __CF_VIEW_H__
#define __CF_VIEW_H__

#include <gtk/gtk.h>

#define CF_COL_SIZE 7
#define CF_ROW_SIZE 6

#define CF_TITLE_TURN_ONE "Turn: Player Yellow"
#define CF_TITLE_TURN_TWO "Turn: Player Red"
#define CF_TITLE_WON_ONE "Player Yellow has won!"
#define CF_TITLE_WON_TWO "Player Red has won!"
#define CF_TITLE_DRAW "Draw!"

#define CF_CLASS_GRID "cf-grid"

class CfField;

class CfView {
private:
    /* Container */
    GtkWidget *grid;

    /* Connection to header bar */
    GtkWidget *hbar;

    /* Fields */
    CfField *field[CF_COL_SIZE][CF_ROW_SIZE];

    /* States */
    gboolean running;
    gint round;

public:
    CfField *(*get_field())[CF_ROW_SIZE];
    void reset();
    GtkWidget *get_viewport();
    gboolean get_running();
    void set_running(gboolean);
    gint get_round();
    void set_round(gint round);
    GtkWidget *get_header_bar();
    void set_header_bar(GtkWidget *);
    CfView();
};

#endif /* __CF_VIEW_H__ */