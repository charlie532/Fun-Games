#ifndef __CF_CHECK_H__
#define __CF_CHECK_H__

#include "cf-view.h"
#include <gtk/gtk.h>

#define NUM_TO_WIN 4

#define CF_MARKUP_WON "<span size='30000' color='#000000'>✓</span>"

class CfField;

gboolean cf_check_get_won(CfField *(*)[CF_ROW_SIZE]);
CfField *cf_check_get_lowest_field(CfField *(*)[CF_ROW_SIZE], CfField *);

#endif /* __CF_CHECK_H__ */
