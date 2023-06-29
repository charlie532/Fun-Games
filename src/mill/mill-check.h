#ifndef __MILL_CHECK_H__
#define __MILL_CHECK_H__

#include "mill-field.h"
#include "mill-view.h"
#include <gtk/gtk.h>

gint mill_check_get_free_fields(MillField *(*)[MILL_SIZE], MillOwner);

gboolean mill_check_get_field_in_range(MillField *(*)[MILL_SIZE], MillField *, MillField *);

gint mill_check_get_field_in_mill(MillField *(*)[MILL_SIZE], MillField *);

#endif /* __MILL_CHECK_H__ */
