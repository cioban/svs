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
#include <glib.h>
#include "config.h"
#include "database.h"
#include "gui.h"

static struct config *conf = NULL;
static unsigned char initbyte = 0;
static int pport_addr = 0;
static int leds_status = 0;
static int leds_timmer = 0;
static int leds_t_pulse = 0;
static int leds_count = 0;
static struct paper_info *info = NULL;

void leds_off(void)
{
    /* Apaga todos os leds  */
    outb(0x00, pport_addr);
    leds_status = 0;
}


void leds_on(void)
{
    /* Acende todos os leds  */
    outb(0x0f, pport_addr);
    leds_status = 1;
}

void led_on(int led)
{
    unsigned char outbyte = 0;

    if(((info->paper > 0) || (conf->test_mode != 0)) && (led > 0)) {
        switch (led) {
            case 1:
                outbyte = 0x01;
            break;
            case 2:
                outbyte = 0x02;
            break;
            case 3:
                outbyte = 0x04;
            break;
            case 4:
                outbyte = 0x08;
            break;
        }
        outb(outbyte, pport_addr);
        leds_status = 0;
    }
#ifdef DEBUG
    fprintf(stderr, "[%s] info->paper(%d) led(%d)\n", __FUNCTION__, info->paper, led);
#endif
    return;
}

gboolean leds_pulse(gpointer data)
{
    leds_on();
    usleep(50000);
    leds_off();
    return TRUE;
}

gboolean leds_blink(gpointer data)
{
    if (leds_status == 0) {
        leds_on();
    } else {
        leds_off();
    }
    return TRUE;
}

gboolean leds_blink_ok(gpointer data)
{
    int count_max = GPOINTER_TO_INT(data);
    if (leds_count > count_max) {
        leds_off();
        leds_count = 0;
        if ((conf->test_mode != 0)) {
            leds_t_pulse = g_timeout_add(1000, leds_pulse, NULL);
        }
        return FALSE;
    }

    leds_blink(NULL);
    leds_count++;
    return TRUE;
}

gpointer write_feedback(gpointer data)
{
    struct feedback *vote = data;

    fprintf(stderr, "[%s] VOTOU: feedback->room(%d) feedback->paper(%d) feedback->button(%d)\n", __FUNCTION__, vote->room, vote->paper, vote->button);

    db_write_feedback(vote);
    g_free(vote);

    return NULL;
}


gboolean pport_update(gpointer data)
{
    static unsigned char button = 0;
    static int intbutton = 0;
    static int auxflag = 0;
    unsigned char readbyte = 0;
    struct feedback *vote = NULL;
    GThread *thr;
    GError *err;

    info = get_paper_info();

    readbyte = inb(pport_addr + 1);
    if (readbyte != initbyte) {
        if(auxflag != 1) {
            auxflag = 1;
            button = initbyte ^ readbyte;

            switch (button) {
                case BTN1:
                    intbutton = 1;
                    if (leds_t_pulse > 0) {
                        g_source_remove(leds_t_pulse);
                    }
                    if (leds_timmer > 0) {
                        g_source_remove(leds_timmer);
                    }
                    leds_count = 0;
#ifdef DEBUG
                    printf(" [%s] Botao 1 [0x%02x] INIT[0x%02x] - Botao[0x%02x]\n", __FUNCTION__, readbyte, initbyte, button);
#endif
                    break;
                case BTN2:
                    intbutton = 2;
                    if (leds_t_pulse > 0) {
                        g_source_remove(leds_t_pulse);
                    }
                    if (leds_timmer > 0) {
                        g_source_remove(leds_timmer);
                    }
                    leds_count = 0;
#ifdef DEBUG
                    printf(" [%s] Botao 2 [0x%02x] INIT[0x%02x] - Botao[0x%02x]\n", __FUNCTION__, readbyte, initbyte, button);
#endif
                    break;
                case BTN3:
                    intbutton = 3;
                    if (leds_t_pulse > 0) {
                        g_source_remove(leds_t_pulse);
                    }
                    if (leds_timmer > 0) {
                        g_source_remove(leds_timmer);
                    }
                    leds_count = 0;
#ifdef DEBUG
                    printf(" [%s] Botao 3 [0x%02x] INIT[0x%02x] - Botao[0x%02x]\n", __FUNCTION__, readbyte, initbyte, button);
#endif
                    break;
                case BTN4:
                    intbutton = 4;
                    if (leds_t_pulse > 0) {
                        g_source_remove(leds_t_pulse);
                    }
                    if (leds_timmer > 0) {
                        g_source_remove(leds_timmer);
                    }
                    leds_count = 0;
#ifdef DEBUG
                    printf(" [%s] Botao 4 [0x%02x] INIT[0x%02x] - Botao[0x%02x]\n", __FUNCTION__, readbyte, initbyte, button);
#endif
                    break;
                default:
                    intbutton = 0;
                    if (leds_t_pulse > 0) {
                        g_source_remove(leds_t_pulse);
                    }

                    if (leds_timmer > 0) {
                        g_source_remove(leds_timmer);
                    }
                    leds_off();
                    printf(" [%s] Botao invalido [0x%02x] INIT[0x%02x] - Botao[0x%02x]\n", __FUNCTION__, readbyte, initbyte, button);
                    break;
           }
           
           led_on(intbutton);
        }
    }

    if((readbyte == initbyte) && (auxflag == 1)) {
        auxflag = 0;

        /* printf(" [%s] TESTE Botao [0x%02x] INIT[0x%02x] - Botao[0x%02x]\n", __FUNCTION__, readbyte, initbyte, button); */

        vote = g_new0(struct feedback, 1); 
        if (vote == NULL) {
            fprintf(stderr, " ERRO!!! Impossivel alocar memoria para vote = g_new0(struct feedback, 1)\n"); 
            exit(1);
        }

        if ( (((conf->room > 0) && (info->paper > 0)) || (conf->test_mode != 0))  && (intbutton > 0)) {

            vote->room   = conf->room;
            vote->paper  = info->paper;
            vote->button = intbutton;

            usleep(100000);
            thr = g_thread_create(write_feedback, vote, FALSE, &err);
            leds_timmer = g_timeout_add(100, leds_blink_ok, GINT_TO_POINTER(10));

            g_timeout_add(100, update_status, GINT_TO_POINTER(15));


            if( thr == NULL ) {
                fprintf(stderr, "g_thread_create error!!!\n");
            }

        }

        button = 0;
        intbutton = 0;
    }
    return TRUE;
}

int pport_init(void)
{
    printf("**** pport_init ****\n");
    conf =  get_config();

    pport_addr = strtol(conf->pport_addr, NULL, 16);

    if( ioperm(pport_addr, 3, 1) != 0) {
        printf(" [%s] ERRO!!! Impossivel acessar a porta paralela ioperm FAIL", __FUNCTION__);
        exit(1);
    }

    leds_off();
    leds_on();
    sleep(1);
    return 0;
}



int pport_loop(void)
{
    printf("**** pport_loop ****\n");
    int pport_timmer = 0;

    initbyte = inb(pport_addr + 1);
    printf("Valor inicial da porta paralela: [0x%02x]\n", initbyte);

    pport_timmer = g_timeout_add(100, pport_update, NULL);
    leds_timmer = g_timeout_add(100, leds_blink_ok, GINT_TO_POINTER(10));

    return 0;
}

int pport_end(void)
{
    leds_off();
    ioperm(pport_addr, 3, 0);
    return 0;
}
