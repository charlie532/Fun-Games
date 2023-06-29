#ifndef __CHKS_VIEW_H__
#define __CHKS_VIEW_H__

#include <gtk/gtk.h>

#define CHKS_SIZE 8

#define CHKS_TITLE_MOVE_ONE "Move: Player White"
#define CHKS_TITLE_MOVE_TWO "Move: Player Black"
#define CHKS_TITLE_TAKE_ONE "Take: Player White"
#define CHKS_TITLE_TAKE_TWO "Take: Player Black"
#define CHKS_TITLE_WON_ONE  "Player White has won!"
#define CHKS_TITLE_WON_TWO  "Player Black has won!"

#define CHKS_CLASS_GRID "chks-grid"

typedef enum {
    CHKS_STATUS_NONE,
    CHKS_STATUS_MOVE,
    CHKS_STATUS_JUMP_AGAIN,
} ChksStatus;

class ChksField;

class ChksView {
private:
    /* Container */
    GtkWidget *grid;

    /* Connection to header bar */
    GtkWidget *hbar;

    /* Fields */
    ChksField *field[CHKS_SIZE][CHKS_SIZE];
    ChksField *last;

    /* States */
    ChksStatus status;
    gint round;
    gint pieces_one;
    gint pieces_two;

public:
    void set_status(ChksStatus );
    void jump(ChksField *);
    void move(ChksField *);
    void reset();
    ChksField *(*get_field())[CHKS_SIZE];
    ChksField *get_last();
    ChksStatus get_status();
    gint get_round();
    GtkWidget *get_viewport();
    void set_header_bar(GtkWidget *hbar);
    ChksView();
};

#endif /* __CHKS_VIEW_H__ */