#include "cf-field.h"
#include "cf-check.h"
#include "cf-view.h"

static void cf_check_set_mark_won(CfField *field[NUM_TO_WIN]) {
    for (gint i = 0; i < NUM_TO_WIN; ++i) {
        GtkWidget *widget = field[i]->get_button();
        GtkWidget *label = gtk_bin_get_child(GTK_BIN(widget));
        gtk_label_set_markup(GTK_LABEL(label), CF_MARKUP_WON);
    }
}

static gboolean cf_check_get_match(CfField *group[NUM_TO_WIN]) {
    CfOwner owner[NUM_TO_WIN];

    /* Collect owners */
    for (gint i = 0; i < NUM_TO_WIN; ++i) {
        owner[i] = group[i]->get_owner();
    }

    /* Check for empty field */
    for (gint i = 0; i < NUM_TO_WIN; ++i) {
        if (owner[i] == CF_OWNER_NONE) return FALSE;
    }

    if (owner[0] == owner[1] && owner[1] == owner[2] && owner[2] == owner[3]) {
        cf_check_set_mark_won(group);
        return TRUE;
    } else {
        return FALSE;
    }
}

gboolean cf_check_get_won(CfField *(*field)[CF_ROW_SIZE]) {
    CfField *group[NUM_TO_WIN];

    static gint col[24][NUM_TO_WIN] = {
        {0, 1, 2, 3}, {0, 1, 2, 3}, {0, 1, 2, 3},
        {0, 1, 2, 3}, {0, 1, 2, 3}, {0, 1, 2, 3},

        {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
        {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1},
        {2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2},
        {3, 3, 3, 3}, {3, 3, 3, 3}, {3, 3, 3, 3},

        {0, 1, 2, 3}, {0, 1, 2, 3}, {0, 1, 2, 3},
        {0, 1, 2, 3}, {0, 1, 2, 3}, {0, 1, 2, 3},
    };

    static gint row[24][NUM_TO_WIN] = {
        {0, 0, 0, 0}, {1, 1, 1, 1}, {2, 2, 2, 2},
        {3, 3, 3, 3}, {4, 4, 4, 4}, {5, 5, 5, 5},

        {0, 1, 2, 3}, {1, 2, 3, 4}, {2, 3, 4, 5},
        {0, 1, 2, 3}, {1, 2, 3, 4}, {2, 3, 4, 5},
        {0, 1, 2, 3}, {1, 2, 3, 4}, {2, 3, 4, 5},
        {0, 1, 2, 3}, {1, 2, 3, 4}, {2, 3, 4, 5},

        {0, 1, 2, 3}, {1, 2, 3, 4}, {2, 3, 4 ,5},
        {5, 4, 3, 2}, {4, 3, 2, 1}, {3, 2, 1, 0},
    };

    for (gint i = 0; i < NUM_TO_WIN; ++i) {
        for (gint j = 0; j < 24; ++j) {
            for (gint k = 0; k < NUM_TO_WIN; ++k) {
                group[k] = field[col[j][k]+i][row[j][k]];
            }
            if (cf_check_get_match(group)) return TRUE;
        }
    }

    return FALSE;
}

CfField *cf_check_get_lowest_field(CfField *(*field)[CF_ROW_SIZE], CfField *start) {
    gint col = start->get_col();

    for (gint row = 5; row >= 0; row--) {
        CfOwner owner = field[col][row]->get_owner();
        if (owner == CF_OWNER_NONE) return field[col][row];
    }

    return NULL;
}