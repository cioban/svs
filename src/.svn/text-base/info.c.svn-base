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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "database.h"
#include "config.h"
#include "gui.h"

static struct config *conf = NULL;
static struct paper_info *info = NULL;
static struct room_info *r_info = NULL;


void info_destroy(struct paper_info *info_d)
{
    if (info_d != NULL) {
        g_free(info_d->person_name);
        g_free(info_d->paper_name);

        g_free(info_d);
    }
}

void info_clean(void)
{

    fprintf(stdout, " [%s] Nao existe nenhuma palestra para votacao...\n", __FUNCTION__);

    if(info == NULL) {
        info = g_new0(struct paper_info, 1);
        if(info == NULL) {
            fprintf(stderr, " [%s] ERRO!!! nao foi possivel alocar memoria para info [info = g_new0(struct paper_info, 1);] \n", __FUNCTION__);
            exit(1);
        }
    }

    info->paper    = 0;
    info->person   = 0;
    info->person_name  = g_strdup("Nenhum palestrante");
    info->paper_name   = g_strdup("Nenhuma palestra selecionada");
    

    return;
}


void info_eval_mode(void)
{

    if(info == NULL) {
        info = g_new0(struct paper_info, 1);
        if(info == NULL) {
            fprintf(stderr, " [%s] ERRO!!! nao foi possivel alocar memoria para info [info = g_new0(struct paper_info, 1);] \n", __FUNCTION__);
            exit(1);
        }
    }

    info->paper    = conf->event_evaluation_paper;
    info->person   = 0;
    info->person_name  = g_strdup("EVAL MODE");
    info->paper_name   = g_strdup("EVAL MODE");

    return;
}

void info_test_mode(void)
{

    if(info == NULL) {
        info = g_new0(struct paper_info, 1);
        if(info == NULL) {
            fprintf(stderr, " [%s] ERRO!!! nao foi possivel alocar memoria para info [info = g_new0(struct paper_info, 1);] \n", __FUNCTION__);
            exit(1);
        }
    }

    if(r_info == NULL) {
        r_info = g_new0(struct room_info, 1);
        if (r_info == NULL) {
            fprintf(stderr,"i [%s] - ERRO!! r_info = NULL \n", __FUNCTION__);
            exit(1);
        }
    }

    info->paper    = 0;
    info->person   = 0;
    info->person_name  = g_strdup("TEST MODE");
    info->paper_name   = g_strdup("TEST MODE");

    r_info->room        = 0;
    r_info->room_name   = g_strdup("TEST MODE");

    return;
}


struct paper_info *info_cp(struct paper_info *db_info)
{
    struct paper_info *ret_info = NULL;

    if (db_info == NULL) {
        return NULL;
    }

    ret_info = g_new0(struct paper_info, 1);
    if(ret_info == NULL) {
        return NULL;
    }

    ret_info->paper    = db_info->paper;
    ret_info->person   = db_info->person;
    ret_info->person_name  = g_strdup(db_info->person_name);
    ret_info->paper_name   = g_strdup(db_info->paper_name);

    info_destroy(db_info);

    return ret_info;
}


struct paper_info *get_paper_info(void)
{
    return info;
}

struct room_info *get_room_info(void)
{
    return r_info;
}


void print_paper_info(struct paper_info *info)
{
    if (info != NULL) {
        fprintf(stderr, "[%s] ########## info->paper(%d) info->person(%d) info->person_name(%s) info->paper_name(%s)\n",
                                __FUNCTION__, info->paper, info->person,
                                info->person_name, info->paper_name);
    } else {
        fprintf(stderr, "[%s] ########## struct paper_info *info = NULL\n", __FUNCTION__);
    }
}

void print_room_info(struct room_info *rinfo)
{
    if (rinfo != NULL) {
        fprintf(stderr, "[%s] ########## rinfo->room(%d) rinfo->room_name(%s)\n",
                                __FUNCTION__, rinfo->room, rinfo->room_name);
    } else {
        fprintf(stderr, "[%s] ########## struct room_info *rinfo = NULL\n", __FUNCTION__);
    }
}



gboolean update_paper_info(gpointer data)
{
    struct paper_info *db_info = NULL;

    /* printf(" - Pooling INFO...\n"); */
    db_info = db_get_paper_info();

    if(db_info == NULL) {
    	/*printf(" [%s] - db_info == NULL \n", __FUNCTION__); */
        if (info->paper != 0) {
            info_clean();
        }
        return TRUE;
    }
    /*print_paper_info(db_info);
    print_paper_info(info);*/

    if (db_info->paper != info->paper) {
    	printf(" [%s] - Alterada a palestra de %d(%s) para %d(%s)\n", __FUNCTION__, info->paper, info->paper_name, db_info->paper, db_info->paper_name);
        info = info_cp(db_info);
        gui_update_paper_data();
    }

    return TRUE;
}


void info_loop(void)
{
    struct paper_info *db_info = NULL;
    int srctimer = 0;

    printf("**** info_loop ****\n");
    
    conf = get_config();    

    if (conf->test_mode == 0) {
        if (conf->event_evaluation == 0) {
            r_info = db_get_room_info(conf->room);
            printf(" [%s] - Sala selecionada %d (%s)\n", __FUNCTION__, r_info->room, r_info->room_name);
            db_info = db_get_paper_info();
            if (db_info != NULL) {
                info = info_cp(db_info);
                printf(" [%s] - Palestra selecionada %d (%s)\n", __FUNCTION__, info->paper, info->paper_name);
              
            } else {
                info_clean();
            }
            srctimer = g_timeout_add(5000, update_paper_info, NULL);
        } else {
            info_eval_mode();
        }
    } else {
        printf(" [%s] - Sala selecionada %d\n", __FUNCTION__, conf->room);
        info_test_mode();
    }

    return;
}

