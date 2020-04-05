/**
 * @file
 * @brief
 * @details
 *
 * @date создан 5.05.2019
 * @author Nick Egorrov
 * @copyright Copyright (C) 2019  Nick Egorrov
 * @copyright
 *      This program is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 * @copyright
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.*
 * @copyright
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <ums/core.h>
#include "init.h"

void
ums_core_init(
        int log_level)
{
        ums_error_init();
        ums_logger_set_level(ums_error_get_logger(), log_level);
        ums_builder_init();
        ums_generator_init();
        ums_simulator_init();
}
