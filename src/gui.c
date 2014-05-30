/**
 *  This file is part of SVS.
 *
 *  SVS is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SVS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with SVS.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <gtk/gtk.h>
#include <glib.h>
#include <time.h>
#include <string.h>
#include "gui.h"
#include "info.h"
#include "config.h"
#include "logo.xpm"

#define EXTERNAL_LOGO 0
#define PATH_LOGO "/usr/share/pixmaps/svs_logo.png"

static GtkWidget *status_label, *speaker_name_label, *paper_name_label;
extern char *svs_version;
static struct config *conf = NULL;

void gui_update_paper_data(void)
{
    char *output;
    struct paper_info *paper_data = NULL;

    gtk_widget_hide(speaker_name_label);
    gtk_widget_hide(paper_name_label);

    paper_data = get_paper_info();

    output = g_markup_printf_escaped("<span size='30000'><i>%s</i></span>", g_convert(paper_data->paper_name, -1, "UTF-8", "ISO-8859-1", NULL, NULL, NULL));
    gtk_label_set_markup(GTK_LABEL(paper_name_label), output);
    if ((paper_data->paper != 0) && (strlen(paper_data->paper_name)>50)) {
        gtk_widget_set_size_request(paper_name_label, 770, -1);
        gtk_label_set_line_wrap(GTK_LABEL(paper_name_label), TRUE);
        gtk_label_set_justify(GTK_LABEL(paper_name_label), GTK_JUSTIFY_FILL);
    } else {
        gtk_widget_set_size_request(paper_name_label, 770, -1);
        gtk_label_set_line_wrap(GTK_LABEL(paper_name_label), FALSE);
        gtk_label_set_justify(GTK_LABEL(paper_name_label), GTK_JUSTIFY_CENTER);
    }

    output = g_markup_printf_escaped("<span size='20000'>%s</span>", g_convert(paper_data->person_name, -1, "UTF-8", "ISO-8859-1", NULL, NULL, NULL));
    gtk_label_set_markup(GTK_LABEL(speaker_name_label), output);

    gtk_widget_show(speaker_name_label);
    gtk_widget_show(paper_name_label);
    g_free(output);

}

gboolean update_status(gpointer data)
{
    int max_count = GPOINTER_TO_INT(data);
    static int status_count = 0;

    if (status_count >= max_count) {
        gtk_widget_hide(status_label);
        status_count = 0;
        return FALSE;
    }

    gtk_widget_show(status_label);
    status_count++;
    return TRUE;
}



gboolean update_clock(gpointer clock)
{
    char *output;
    time_t simple_time;
    struct tm *time_info;
    gchar *str = g_new(gchar, 50);

    time (&simple_time);
    time_info = localtime(&simple_time);
    
    strftime(str, 50, "%d/%m/%Y %T", time_info);

    output = g_markup_printf_escaped("<span size='20000'><b>%s</b></span>", str);
    gtk_label_set_markup(GTK_LABEL(clock), output);
    gtk_label_set_justify(GTK_LABEL(clock), GTK_JUSTIFY_LEFT);

    gtk_widget_show(clock);

    g_free(str);
    g_free(output);

    return TRUE;
}




/*-- This function allows the program to exit properly when the window is closed --*/
gint destroyapp (GtkWidget *widget, gpointer gdata)
{
  //g_print ("Quitting...\n");
  gtk_main_quit();
  return (FALSE);
}

int gui_init (void)
{
	/*-- Declare the GTK Widgets used in the program --*/
	GtkWidget *window;
	GtkWidget *clock, *paper_label, *room_label, *speaker_label, *space_label2, *title, *label, *label2, *evallabel1, *evallabel2, *evallabel3;
	GtkWidget *vbox;
	char *output;
	struct paper_info *paper_data = NULL;
	struct room_info *room_data = NULL;
	GtkWidget *logo;

    conf =  get_config();

    if (conf->event_evaluation == 0) {
        room_data = get_room_info();
    }
    paper_data = get_paper_info();


  /*--  Initialize GTK --*/
  gtk_init (NULL, NULL);

  /*-- Create the new window --*/
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  //gtk_window_fullscreen(GTK_WINDOW(window));

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
  gtk_window_set_title(GTK_WINDOW(window), "SVS - Sistema de Votacao SoLiSC");
  GTK_WINDOW(window)->allow_shrink = TRUE;
  GTK_WINDOW(window)->allow_grow = TRUE;
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  title = gtk_label_new(NULL);
  output = g_markup_printf_escaped("<span size='12000' color='#a00000'>SVS - Sistema de Votacao SoLiSC - %s - http://code.google.com/p/svsolisc/ - cioban@solisc.org.br</span>", svs_version);
  gtk_label_set_markup(GTK_LABEL(title), output);

    vbox = gtk_vbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), title, FALSE, TRUE, 0);


#if EXTERNAL_LOGO == 1
	logo = gtk_image_new_from_file(PATH_LOGO);
#else
	GdkPixbuf *XPM;
	XPM = gdk_pixbuf_new_from_xpm_data(logo_xpm);
	logo = gtk_image_new_from_pixbuf(XPM);
#endif


    gtk_box_pack_start(GTK_BOX(vbox), logo, FALSE, FALSE, 10);
	gtk_widget_show_all(vbox);


    if (conf->event_evaluation == 0) {
        room_label = gtk_label_new(NULL);
        output = g_markup_printf_escaped("<span size='30000'><b>Sala:</b> %s</span>", room_data->room_name);
        gtk_label_set_markup(GTK_LABEL (room_label), output);

        label = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(label), "<span size='40000' color='#001bbd'><b>Contribua com o 5º SoLiSC</b></span>");
        label2 = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(label2), "<span size='40000' color='#001bbd'><b>Avalie a palestra!!!</b></span>");

        //space_label = gtk_label_new(NULL);
        //gtk_label_set_markup(GTK_LABEL(space_label), "<span size='20000'> </span>");
        space_label2 = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(space_label2), "<span size='20000'> </span>");

        paper_label = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(paper_label), "<span size='30000'><b>Palestra</b></span>");

        paper_name_label = gtk_label_new(NULL);
        output = g_markup_printf_escaped("<span size='30000'><i>%s</i></span>", g_convert(paper_data->paper_name, -1, "UTF-8", "ISO-8859-1", NULL, NULL, NULL));
        gtk_label_set_markup(GTK_LABEL(paper_name_label), output);
        gtk_widget_set_size_request(paper_name_label, 770, -1);
        if ((paper_data->paper != 0) && (strlen(paper_data->paper_name)>45)) {
            gtk_label_set_line_wrap(GTK_LABEL(paper_name_label), TRUE);
            gtk_label_set_justify(GTK_LABEL(paper_name_label), GTK_JUSTIFY_FILL);
        } else {
            gtk_label_set_line_wrap(GTK_LABEL(paper_name_label), FALSE);
            gtk_label_set_justify(GTK_LABEL(paper_name_label), GTK_JUSTIFY_CENTER);
        }

        speaker_label = gtk_label_new(NULL);
        output = g_markup_printf_escaped("<span size='20000'><b>Palestrante:</b></span>");
        gtk_label_set_markup(GTK_LABEL(speaker_label), output);

        speaker_name_label = gtk_label_new(NULL);
        output = g_markup_printf_escaped("<span size='20000'>%s</span>", g_convert(paper_data->person_name, -1, "UTF-8", "ISO-8859-1", NULL, NULL, NULL));
        gtk_label_set_markup(GTK_LABEL(speaker_name_label), output);

        gtk_box_pack_start(GTK_BOX(vbox), room_label, FALSE, TRUE, 20);
        gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox), label2, FALSE, TRUE, 0);
        //gtk_box_pack_start(GTK_BOX(vbox), space_label, FALSE, TRUE, 10);
        gtk_box_pack_start(GTK_BOX(vbox), paper_label, FALSE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox), paper_name_label, FALSE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox), space_label2, FALSE, TRUE, 10);
        gtk_box_pack_start(GTK_BOX(vbox), speaker_label, FALSE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox), speaker_name_label, FALSE, TRUE, 0);

    } else {
        //space_label = gtk_label_new(NULL);
        //gtk_label_set_markup(GTK_LABEL(space_label), "<span size='40000'> </span>");

        evallabel1 = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(evallabel1), "<span size='60000' color='#001bbd'><b>Qual é a sua opinião</b></span>");
        evallabel2 = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(evallabel2), "<span size='60000' color='#001bbd'><b>sobre o 5º SoLiSC?</b></span>");
        evallabel3 = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(evallabel3), "<span size='60000' color='#001bbd'><b>Avalie o evento!!!</b></span>");
        //gtk_box_pack_start(GTK_BOX(vbox), space_label, FALSE, TRUE, 10);
        gtk_box_pack_start(GTK_BOX(vbox), evallabel1, FALSE, TRUE, 10);
        gtk_box_pack_start(GTK_BOX(vbox), evallabel2, FALSE, TRUE, 10);
        gtk_box_pack_start(GTK_BOX(vbox), evallabel3, FALSE, TRUE, 10);

    }

    status_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(status_label), "<span size='30000' color='red'>Agradecemos a sua opinião!!!</span>");

    clock = gtk_label_new(NULL);
    gtk_widget_set_size_request(clock, 770, -1);
    gtk_label_set_justify(GTK_LABEL(clock), GTK_JUSTIFY_LEFT);

    gtk_box_pack_start(GTK_BOX(vbox), status_label, TRUE, TRUE, 10);
    gtk_box_pack_end(GTK_BOX(vbox), clock, FALSE, FALSE, 1);

    /*-- Connect the window to the destroyapp function  --*/
    gtk_signal_connect(GTK_OBJECT(window), "delete_event", GTK_SIGNAL_FUNC(destroyapp), NULL);

    gtk_container_add(GTK_CONTAINER(window), vbox);


    gtk_widget_show_all(window);
    gtk_widget_hide(status_label);
    gtk_widget_hide(clock);


   g_timeout_add(1000, update_clock, (gpointer)clock); 

    g_free(output);

  /*-- Start the GTK event loop --*/
  gtk_main();

  /*-- Return 0 if exit is successful --*/
  return 0;
}
