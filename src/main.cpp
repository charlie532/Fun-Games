/* c-basic-offset: 4; tab-width: 8; indent-tabs-mode: nil
 * vi: set shiftwidth=4 tabstop=8 expandtab:
 * :indentSize=4:tabSize=8:noTabs=true:
 */

#include "window.h"
#include <gtk/gtk.h>

gint main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GBoxWindow win;
    GtkWidget *start_window = win.get_gbox_window();

    gtk_widget_show_all(start_window);

    gtk_main();
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 4
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=4 tabstop=8 expandtab:
 * :indentSize=4:tabSize=8:noTabs=true:
 */
