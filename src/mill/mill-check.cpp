#include "mill-check.h"
#include "mill-view.h"

static gboolean mill_check_get_is_mill(MillField *group[3]) {
    MillOwner owner[3];

    for (gint i = 0; i < 3; ++i) {
        owner[i] = group[i]->get_owner();

        if (owner[i] == MILL_OWNER_NONE) return FALSE;
    }

    if (owner[0] == owner[1] && owner[1] == owner[2]) return TRUE;

    return FALSE;
}

gint mill_check_get_free_fields(MillField *(*field)[MILL_SIZE], MillOwner  owner) {
    gint free_cnt = 0;

    for (gint i = 0; i < MILL_SIZE; ++i) {
        for (gint j = 0; j < MILL_SIZE; ++j) {
            MillOwner tmp = field[i][j]->get_owner();
            gint cnt = mill_check_get_field_in_mill(field, field[i][j]);

            /* If the field belongs to the enemy and is not in a mill */
            if (cnt == 0 && tmp == owner) free_cnt++;
        }
    }

    return free_cnt;
}

gboolean mill_check_get_field_in_range(MillField *(*field)[MILL_SIZE], MillField *piece, MillField *dest) {
    gint start_x = piece->get_col();
    gint start_y = piece->get_row();

    gint dest_x = dest->get_col();
    gint dest_y = dest->get_row();

    gint diff_x = dest_x - start_x;
    gint diff_y = dest_y - start_y;

    gint diff = diff_x + diff_y;
    diff = (diff < 0) ? diff * -1 : diff;

    /**
     * If same field is selected
     * or trying to move diagonally
     */
    if ((diff_x == 0 && diff_y == 0) ||
        (diff_x != 0 && diff_y != 0))
            return FALSE;

    /* One step always works */
    if (diff == 1) return TRUE;

    /* Check if the range is too big */
    if (diff > 3) return FALSE;

    /* Checking fields in between start and destination */
    gboolean vertical = (diff_y == 0) ? FALSE : TRUE;

    if (vertical) {
        gint tmp_y = (dest_y > start_y) ? dest_y : start_y;
        gint tmp_x = dest_x;
        while (--diff > 0) {
            MillOwner owner = field[tmp_x][tmp_y-diff]->get_owner();

            if ((tmp_x == 3 && tmp_y-diff == 3) || owner != MILL_OWNER_BLOCK) return FALSE;

            diff--;
        }
    } else {
        gint tmp_x = (dest_x > start_x) ? dest_x : start_x;
        gint tmp_y = dest_y;
        while (--diff > 0) {
            MillOwner owner = field[tmp_x-diff][tmp_y]->get_owner();

            if ((tmp_x-diff == 3 && tmp_y == 3) || owner != MILL_OWNER_BLOCK) return FALSE;

            diff--;
        }
    }

    return TRUE;
}

gint mill_check_get_field_in_mill(MillField *(*field)[MILL_SIZE], MillField *piece) {
    MillField *group[3];
    gint mill_cnt = 0;

    static gint mill_x[16][3] = {
            {0, 3, 6}, {1, 3, 5}, {2, 3, 4},
            {0, 1, 2}, {4, 5, 6},
            {2, 3, 4}, {1, 3, 5}, {0, 3, 6},

            {0, 0, 0}, {1, 1, 1}, {2, 2, 2},
            {3, 3, 3}, {3, 3, 3},
            {4, 4, 4}, {5, 5, 5}, {6, 6, 6},
    };

    static gint mill_y[16][3] = {
            {0, 0, 0}, {1, 1, 1}, {2, 2, 2},
            {3, 3, 3}, {3, 3, 3},
            {4, 4, 4}, {5, 5, 5}, {6, 6, 6},

            {0, 3, 6}, {1, 3 ,5}, {2, 3, 4},
            {0, 1, 2}, {4, 5, 6},
            {2, 3, 4}, {1, 3, 5}, {0, 3, 6},
    };

    for (gint i = 0; i < 16; ++i) {
        for (gint j = 0; j < 3; ++j) {
            group[j] = field[mill_x[i][j]][mill_y[i][j]];
        }
        
        if (group[0] != piece &&
            group[1] != piece &&
            group[2] != piece)
                continue;

        if (mill_check_get_is_mill(group)) mill_cnt++;
    }

    return mill_cnt;
}
