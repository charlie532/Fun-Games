/* c-basic-offset: 4; tab-width: 8; indent-tabs-mode: nil
 * vi: set shiftwidth=4 tabstop=8 expandtab:
 * :indentSize=4:tabSize=8:noTabs=true:
 */

#include "window.h"
#include <gtk/gtk.h>

using namespace std;

gint main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GBoxWindow win;
    GtkWidget *wid_gtk = win.gbox_window_get();

    gtk_widget_show_all(wid_gtk);

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
