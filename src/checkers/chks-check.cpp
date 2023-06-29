#include "chks-field.h"
#include "chks-check.h"
#include "chks-view.h"

ChksTurn chks_check_get_turn(ChksField *(*field)[CHKS_SIZE], ChksField *start, ChksField *dest) {
	gint start_x = start->get_col();
	gint start_y = start->get_row();
	gint dest_x = dest->get_col();
	gint dest_y = dest->get_row();
	gint diff_x = dest_x - start_x;
	gint diff_y = dest_y - start_y;
	ChksOwner owner = start->get_owner();
	ChksOwner enemy = (owner == CHKS_OWNER_ONE) ? CHKS_OWNER_TWO : CHKS_OWNER_ONE;
	ChksOwner owner_dest = dest->get_owner();
	gboolean is_queen = start->get_is_queen();

	/* Check destination field */
	if (owner_dest != CHKS_OWNER_NONE) return CHKS_TURN_NONE;

	/* Check for one regular step */
	if ((diff_x * diff_x == 1)) {
		if (is_queen && (diff_y * diff_y == 1)) return CHKS_TURN_MOVE;

		if (owner == CHKS_OWNER_ONE && diff_y == -1) return CHKS_TURN_MOVE;

		if (owner == CHKS_OWNER_TWO && diff_y == 1) return CHKS_TURN_MOVE;
	}

	/* Check for two steps */
	if ((diff_x * diff_x == 4)) {
			gint mid_x = (dest_x + start_x) / 2;
			gint mid_y = (dest_y + start_y) / 2;
			ChksOwner owner_mid = field[mid_x][mid_y]->get_owner();

			if (owner_mid != enemy) return CHKS_TURN_NONE;

			if (is_queen && (diff_y * diff_y) == 4) return CHKS_TURN_TAKE;

			if (owner == CHKS_OWNER_ONE && diff_y == -2) return CHKS_TURN_TAKE;

			if (owner == CHKS_OWNER_TWO && diff_y == 2) return CHKS_TURN_TAKE;
	}

	return CHKS_TURN_NONE;
}

gboolean chks_check_get_can_jump_again(ChksField *(*field)[CHKS_SIZE], ChksField *piece) {
	gint start_x = piece->get_col();
	gint start_y = piece->get_row();

	/* Check top/bottom left/right pieces */
	for (gint i = -2; i <= 2; i += 4) {
		for (gint j = -2; j <= 2; j += 4) {
			gint dest_x = start_x + i;
			gint dest_y = start_y + j;

			/* Check if destination field is too far away */
			if (dest_x < 0 || dest_x > 7 || dest_y < 0 || dest_y > 7) continue;

			/* Check if it's possible to jump there */
			ChksTurn turn = chks_check_get_turn(field, piece, field[dest_x][dest_y]);

			if (turn == CHKS_TURN_TAKE) return TRUE;
		}
	}

	return FALSE;
}

gboolean chks_check_get_becomes_queen(ChksField *piece) {
	ChksOwner owner = piece->get_owner();
	gint row = piece->get_row();

	if ((owner == CHKS_OWNER_ONE && row == 0) || (owner == CHKS_OWNER_TWO && row == 7)) return TRUE;
	return FALSE;
}
