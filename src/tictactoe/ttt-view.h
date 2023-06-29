#ifndef __TTT_VIEW_H__
#define __TTT_VIEW_H__

#include <gtk/gtk.h>

#define TTT_SIZE 3
#define TTT_STATE_NUM 3

#define TTT_TITLE_TURN_ONE "Turn: Player X"
#define TTT_TITLE_TURN_TWO "Turn: Player O"

#define TTT_TITLE_WON_ONE "Player X has won!"
#define TTT_TITLE_WON_TWO "Player O has won!"

#define TTT_TITLE_DRAW "Draw!"

class TttField;

class TttView {
private:
    /* Container */
    GtkWidget *grid;

    /* Connection to header bar */
    GtkWidget *hbar;

    /* Fields */
    TttField *field[TTT_SIZE][TTT_SIZE];

    /* States */
    gboolean running;
    gint round;

public:
    void reset();
    gint get_round();
    void set_round(gint);
    gboolean get_running();
    void set_running(gboolean);
    GtkWidget *get_hbar();
    TttField *(*get_field())[TTT_SIZE];
    GtkWidget *get_viewport();
    void set_header_bar(GtkWidget *);
    TttView();
};

#endif /* __TTT_VIEW_H__ */