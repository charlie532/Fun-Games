#ifndef __CHKS_CHECK_H__
#define __CHKS_CHECK_H__

#include "chks-view.h"
#include <gtk/gtk.h>

typedef enum {
	CHKS_TURN_NONE,
	CHKS_TURN_MOVE,
	CHKS_TURN_TAKE,
} ChksTurn;

class ChksField;

ChksTurn chks_check_get_turn(ChksField *(*field)[CHKS_SIZE], ChksField *, ChksField *);

gboolean chks_check_get_can_jump_again(ChksField *(*field)[CHKS_SIZE], ChksField *);

gboolean chks_check_get_becomes_queen(ChksField *piece);

#endif /* __CHKS_CHECK_H__ */