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

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <glib.h>
#include <signal.h>
#include <string.h>
#include "database.h"
#include "config.h"
#include "gui.h"

char *svs_version = NULL;
static struct config *conf = NULL;


void clean_exit(int signal)
{
    fprintf(stderr, "[%s] Saindo corretamente SINAL[%d]...\n", __FUNCTION__, signal);
	db_close();
    pport_end();
    g_free(svs_version);
	exit(0);
}


int main(int argc, char* argv[])
{
    time_t simple_time;
    struct tm *time_info;
    char *plabel = "svs";

    gchar *build = g_new(gchar, 50);
    time (&simple_time);
    time_info = localtime(&simple_time);
    strftime(build, 50, "%Y%m%d%H%M", time_info);
    svs_version = g_strdup_printf("trunk-%s", build);

    g_free(build);


    memset(argv[0], 0, strlen(argv[0]));
    memcpy(argv[0], plabel, strlen(plabel));


    printf ("\n\n############################################################\n");
    printf ("# Sistema de votacao de palestras SoLiSC.org.br\n");
    printf ("# Versao: %s - GPL\n", svs_version);
    printf ("# Sergio Cioban Filho - cioban@gmail.com \n");
    printf ("############################################################\n");

    signal(SIGINT,  clean_exit);
    signal(SIGKILL, clean_exit);
    signal(SIGTERM, clean_exit);

    config_init();

    conf = get_config();

    if (conf->event_evaluation != 0) {
        printf ("\n\n############################################################\n");
        printf ("# EVENT EVALUATION\n");
        printf ("# Sistema em modo de avaliacao do evento...\n");
        printf ("############################################################\n\n");
    }


    if (conf->test_mode != 0) {
        printf ("\n\n############################################################\n");
        printf ("# TEST MODE\n");
        printf ("# Sistema operando em modo de teste, nenhum voto sera computado\n");
        printf ("############################################################\n\n");
    }

    pport_init();
    db_init();

    if (!g_thread_supported ()) g_thread_init (NULL);

    info_loop();

    pport_loop();
    gui_init();
    return 0;
}
