#ifndef __TTT_CHECK_H__
#define __TTT_CHECK_H__

#include "ttt-view.h"
#include <gtk/gtk.h>

class TttField;

gboolean ttt_check_get_won(TttField *(*)[TTT_SIZE]);

#endif /* __TTT_CHECK_H__ */