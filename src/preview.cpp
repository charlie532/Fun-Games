#include "preview.h"

const gchar *GBoxPreview::get_markup_from_title(const gchar *title) {
	static const gchar *markup_p1 = "<span size='25000' color='#21242C'><u>";
	static const gchar *markup_p2 = "</u>\n</span>";
	static gint markup_length = 50;

	gint length = markup_length + strlen(title) + 1;
	gchar *markup = (gchar *)g_malloc(sizeof(gchar) * length);

	strcpy(markup, markup_p1);
	strcat(markup, title);
	strcat(markup, markup_p2);

	return markup;
}

const gchar *GBoxPreview::get_image_path_from_name(const gchar *name) {
	static const gchar *path_default = IMAGES_PATH_DEFAULT;

	static gint path_default_length = 26;

	gint length = path_default_length + strlen(name) + 1;
	gchar *path = (gchar *)g_malloc(sizeof(gchar) * length);

	strcpy(path, path_default);
	strcat(path, name);

	return path;
}

void GBoxPreview::gbox_preview_add_interface() {
	GtkGrid *grid = GTK_GRID(this->grid);
	GtkWidget *placeholder = gtk_label_new(NULL);

	gtk_grid_attach(grid, this->title, 0, 0, 4, 3);
	gtk_grid_attach(grid, this->image, 0, 3, 4, 3);
	gtk_grid_attach(grid, placeholder, 0, 6, 4, 1);
	gtk_grid_attach(grid, this->btn_start, 1, 7, 2, 2);
}

GtkWidget *GBoxPreview::get_viewport() {
	return this->grid;
}

GtkWidget *GBoxPreview::get_start_button() {
	return this->btn_start;
}

void GBoxPreview::set_title(const gchar *title) {
	GtkLabel *label = GTK_LABEL(this->title);
	const gchar *markup = get_markup_from_title(title);

	gtk_label_set_markup(label, markup);
}

void GBoxPreview::set_image_name(const gchar *image_name) {
	GtkImage *image = GTK_IMAGE(this->image);
	const gchar *path = get_image_path_from_name(image_name);

	gtk_image_set_from_file(image, path);
}

GBoxPreview::GBoxPreview() {
	this->grid = gtk_grid_new();
	this->title = gtk_label_new(NULL);
	this->image = gtk_image_new();
	this->btn_start = gtk_button_new_with_label("Start Game");

	/* Grid */
	gtk_container_set_border_width(GTK_CONTAINER(this->grid), 20);
	gtk_grid_set_column_homogeneous(GTK_GRID(this->grid), TRUE);

	/* Add style to button */
	GtkStyleContext *context = gtk_widget_get_style_context(this->btn_start);
	gtk_style_context_add_class(context, "suggested-action");

	gbox_preview_add_interface();
}