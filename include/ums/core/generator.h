/**
 * @file
 * @brief
 * @details
 *
 * @date создан 2.06.2019
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

#ifndef UMS_CORE_GENERATOR_H_
#define UMS_CORE_GENERATOR_H_

#include "device.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ums_generator_o;
extern const ums_class_t UMS_CLASS_GENERATOR;

/*******************************************************************************
 * sections : protected
 ******************************************************************************/

#ifdef _UMS_PROTECTED_

typedef struct ums_generator_o {
        ums_device_o super;

        struct {
                ums_device_reset_f reset;
        } override;

        int flags;

        ums_qword_t period;
        ums_dword_t freq;
        ums_qword_t ticks;
        ums_qword_t base;
} ums_generator_o;

#endif /* _UMS_PROTECTED_ */

#ifdef __cplusplus
}
#endif

#endif /* UMS_CORE_GENERATOR_H_ */
