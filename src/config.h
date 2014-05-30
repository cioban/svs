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

#define CFG_FILE "/etc/svs.conf"


struct config {
    char *pport_addr;

    char *papers_server;
    char *papers_user;
    char *papers_pass;
    char *papers_db;

    char *svs_server;
    char *svs_user;
    char *svs_pass;
    char *svs_db;
    int room;
    int test_mode;
    int event_evaluation;
    int event_evaluation_paper;
};

void config_init(void);
struct config *get_config(void);
