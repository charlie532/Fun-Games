#ifndef __GBOX_PREVIEW_H__
#define __GBOX_PREVIEW_H__

#include "CONFIG.h"
#include <gtk/gtk.h>
#include <string.h>

class GBoxPreview {
private:
	/* Container */
	GtkWidget *grid;

	/* Widgets */
	GtkWidget *title;
	GtkWidget *image;
	GtkWidget *btn_start;

	const gchar *get_markup_from_title(const gchar *);
	const gchar *get_image_path_from_name(const gchar *);
	void gbox_preview_add_interface();
	
public:
	GtkWidget *get_viewport();
	GtkWidget *get_start_button();
	void set_title(const gchar *);
	void set_image_name(const gchar *);
	GBoxPreview();
};

#endif /* __GBOX_PREVIEW_H__ */
