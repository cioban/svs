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


/* Estrutura para armazenar as informacoes da
 * palestra, sala, palestrante da votacao corrente
 */
struct paper_info {
    int paper;
    int person;
    char *person_name;
    char *paper_name;
};

/* Informacoes sobre a sala */
struct room_info {
    int room;
    char *room_name;
};


//gboolean update_paper_info(void);
void info_loop(void);
void print_paper_info(struct paper_info *info);
struct paper_info *get_paper_info(void);
struct room_info *get_room_info(void);
