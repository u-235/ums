/**
 * @file
 * @brief
 * @details
 *
 * @date создан 16.05.2019
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

#ifndef UMS_CORE_BUILDER_H_
#define UMS_CORE_BUILDER_H_

#include "device.h"

#ifdef __cplusplus
extern "C" {
#endif

extern struct ums_device_o *
ums_build(
        const char *name);

/*******************************************************************************
 * sections : protected
 ******************************************************************************/

#ifdef _UMS_PROTECTED_

typedef struct ums_builder_t {
        struct ums_device_o *(*_build)(
                const char *name);
        struct ums_builder_t *_next;
} ums_builder_t;

extern void
ums_builder_add(
        struct ums_builder_t *builder);

#endif /* _UMS_PROTECTED_ */

#ifdef __cplusplus
}
#endif

#endif /* UMS_CORE_BUILDER_H_ */
