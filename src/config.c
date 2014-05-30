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
#include "../lib/obj/include/confuse.h"
#include "config.h"


static struct config *conf = NULL;

void config_init(void)
{
    cfg_t *confusecfg = NULL;
    printf ("** Carregando configuracoes **\n");

    conf = malloc(sizeof(struct config));
    if (conf == NULL) {
        fprintf(stderr, " - Erro ao alocar memoria para configuracao!!!\n");
        goto error;
    }


    cfg_opt_t cfgopts[] = {
        CFG_SIMPLE_STR ("pport_addr", &conf->pport_addr),
        CFG_SIMPLE_STR ("papers_server", &conf->papers_server),
        CFG_SIMPLE_STR ("papers_user", &conf->papers_user),
        CFG_SIMPLE_STR ("papers_pass", &conf->papers_pass),
        CFG_SIMPLE_STR ("papers_db", &conf->papers_db),
        CFG_SIMPLE_STR ("svs_server", &conf->svs_server),
        CFG_SIMPLE_STR ("svs_user", &conf->svs_user),
        CFG_SIMPLE_STR ("svs_pass", &conf->svs_pass),
        CFG_SIMPLE_STR ("svs_db", &conf->svs_db),
        CFG_SIMPLE_INT ("room", &conf->room),
        CFG_SIMPLE_INT ("test_mode", &conf->test_mode),
        CFG_SIMPLE_INT ("event_evaluation", &conf->event_evaluation),
        CFG_SIMPLE_INT ("event_evaluation_paper", &conf->event_evaluation_paper),
        CFG_END()
    };
    confusecfg = cfg_init(cfgopts, 0);
    if(cfg_parse(confusecfg, CFG_FILE) != CFG_SUCCESS) {
        fprintf(stderr, " - Erro ao ler arquivo de configuracao, ou arquivo de configuracao invalido!!!\n");
       goto error;
    }

    printf (" - Arquivo de configuracao lido com sucesso\n");
    printf ("  => Utilizando a porta paralela: %s \n", conf->pport_addr);
    cfg_free(confusecfg);

    return;

error:
        if (confusecfg != NULL) {
            cfg_free(confusecfg);
		}
        exit(1);
}

struct config *get_config(void)
{
    if(conf != NULL){
        return conf;
    } else {
        fprintf(stderr, " - Configuracao NULA, utilize config_init antes de get_config!!!\n");
        exit(1);
    }
}
