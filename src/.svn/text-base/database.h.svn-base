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
#include <mysql/mysql.h>
#include "info.h"
#include "pport.h"

int db_init(void);
void db_close(void);
int get_curr_paper_from_grade(int room);
struct paper_info *db_get_paper_info(void);
struct room_info *db_get_room_info(int room);
void db_write_feedback(struct feedback *vote);
