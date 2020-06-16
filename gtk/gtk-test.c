#include <stdlib.h>
#include <gtk/gtk.h>

void cb_quit(GtkWidget *p_widget, gpointer user_data);

int main(int argc, char **argv) {
    GtkWidget *p_window = NULL;

    //init gtk
    gtk_init(&argc, &argv);

    //create main window
    p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(p_window), "destroy", G_CALLBACK(cb_quit), NULL);
    gtk_window_set_default_size(GTK_WINDOW(p_window), 200, 200);

    // quit button
    {
        GtkWidget *p_button = NULL;

        p_button = gtk_button_new_with_label("Quit");
        gtk_container_add (GTK_CONTAINER (p_window), p_button);
        g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_quit), NULL);
    }

    //display main window
    //gtk_widget_show(p_window);
    gtk_widget_show_all (p_window);

    ///launch main loop
    gtk_main();

    return EXIT_SUCCESS;
}

void cb_quit(GtkWidget *p_widget, gpointer user_data) {
    gtk_main_quit();

    (void) p_widget;
    (void) user_data;
}
