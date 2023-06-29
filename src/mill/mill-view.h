#ifndef __MILL_VIEW_H__
#define __MILL_VIEW_H__

#include <gtk/gtk.h>

#define MILL_SIZE 7

#define MILL_TITLE_PLACE_ONE "Place: Player Green"
#define MILL_TITLE_PLACE_TWO "Place: Player Red"

#define MILL_TITLE_MOVE_ONE  "Move: Player Green"
#define MILL_TITLE_MOVE_TWO  "Move: Player Red"

#define MILL_TITLE_TAKE_ONE  "Take: Player Green"
#define MILL_TITLE_TAKE_TWO  "Take: Player Red"

#define MILL_TITLE_WON_ONE   "Player Green has won!"
#define MILL_TITLE_WON_TWO   "Player Red has won!"

#define MILL_CLASS_GRID "mill-grid"

typedef enum {
    MILL_STATUS_PLACE,
    MILL_STATUS_MOVE,
    MILL_STATUS_TAKE,
    MILL_STATUS_DONE,
} MillStatus;

class MillField;

class MillView {
private:
    /* Container */
    GtkWidget *grid;

    /* Connection to header bar */
    GtkWidget *hbar;

    /* Fields */
    MillField *field[MILL_SIZE][MILL_SIZE];
    MillField *last;

    /* States */
    MillStatus status;
    gint round;
    gint mill_cnt;
    gint pieces_one;
    gint pieces_two;
    
public:
    gint get_piece_one();
    gint get_piece_two();
    MillField *(*get_field())[MILL_SIZE];
    MillField *get_last();
    gint get_round();
    MillStatus get_status();
    void set_status(MillStatus);
    void take(MillField *);
    void move(MillField *);
    void place(MillField *);
    void reset();
    GtkWidget *get_viewport();
    void set_header_bar(GtkWidget *);
    MillView();
};

#endif /* __MILL_VIEW_H__ */