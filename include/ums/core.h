/**
 * @file
 * @brief
 * @details
 *
 * @date создан 20.04.2019
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

#ifndef UMS_CORE_H_
#define UMS_CORE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "core/builder.h"
#include "core/device.h"
#include "core/error.h"
#include "core/logger.h"
#include "core/object.h"
#include "core/simulator.h"

extern void
ums_core_init(
        int log_level);

#ifdef __cplusplus
}
#endif

#endif /* UMS_CORE_H_ */
