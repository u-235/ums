/**
 * @file
 * @brief
 * @details
 *
 * @date создан 3.05.2019
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

#ifndef UMS_CORE_SIMULATOR_H_
#define UMS_CORE_SIMULATOR_H_

#include "device.h"
#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ums_simulator_o;
extern const struct ums_class_t UMS_CLASS_SIMULATOR;

extern struct ums_device_o *
ums_simulator_get(
        void);

extern void
ums_simulator_reset(
        void);

extern ums_time_t
ums_simulator_step(
        ums_time_t max);

extern ums_time_t
ums_simulator_run(
        ums_time_t max);

extern ums_time_t
ums_simulator_breack(
        void);

/*******************************************************************************
 * sections : protected
 ******************************************************************************/

#ifdef _UMS_PROTECTED_

typedef struct ums_simulator_o {
        ums_device_o super;

        ums_list_o all_devices;

        struct {
                void (*run)(
                        ums_device_change_f run_func,
                        struct ums_device_o *dev);
                void (*wait)(void);
        } balancer;
} ums_simulator_o;

#endif /* _UMS_PROTECTED_ */

#ifdef __cplusplus
}
#endif

#endif /* UMS_CORE_SIMULATOR_H_ */
