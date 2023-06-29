#include "ttt-field.h"
#include "ttt-check.h"
#include "ttt-view.h"

static gboolean ttt_check_get_match(TttOwner owner[]) {
	gint i;

	/* Look for non-assigned field */
	for (i = 0; i < TTT_STATE_NUM; ++i) {
		if (owner[i] == TTT_OWNER_NONE) return FALSE;
	}

	return (owner[0] == owner[1]) && (owner[1] == owner[2]);
}

gboolean ttt_check_get_won(TttField *(*field)[TTT_SIZE]) {
	TttOwner group[TTT_SIZE];

	/* Check vertically and horizontally */
	for (gint i = 0; i < TTT_SIZE; ++i) {
		for (gint j = 0; j < TTT_SIZE; ++j) {
			group[j] = field[i][j]->get_owner();
		}

		if (ttt_check_get_match(group)) return TRUE;

		for (gint j = 0; j < TTT_SIZE; ++j) {
			group[j] = field[j][i]->get_owner();
		}

		if (ttt_check_get_match(group)) return TRUE;
	}

	/* Check diagonally */
	for (gint i = 0; i < TTT_SIZE; ++i) {
		group[i] = field[i][i]->get_owner();
	}

	if (ttt_check_get_match(group)) return TRUE;

	for (gint i = 0; i < TTT_SIZE; ++i) {
		group[i] = field[i][TTT_SIZE-1 - i]->get_owner();
	}

	if (ttt_check_get_match(group)) return TRUE;

	return FALSE;
}