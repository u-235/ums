/**
 * @file
 * @brief
 * @details
 *
 * @date создан 30.05.2019
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

#ifndef CORE_DEVICE_H_
#define CORE_DEVICE_H_

#include "list.h"
#include "object.h"
#include "signals.h"
#include "types.h"
#include "property.h"
#include "value.h"

enum device_status {
        DEVICE_OK,
        DEVICE_BREAK,
        DEVICE_ERROR_OUT_OF_RANGE,
        DEVICE_ERROR_OUT_OF_MEMORY,
        DEVICE_ERROR
};

struct ums_device_o;
extern const struct ums_class_t UMS_CLASS_DEVICE;

extern const char *
ums_device_get_name(
        struct ums_device_o *dev);

extern void
ums_device_set_label(
        struct ums_device_o *dev,
        const char *label);

extern const char *
ums_device_get_label(
        struct ums_device_o *dev);

extern int
ums_device_get_id(
        struct ums_device_o *dev);

extern int
ums_device_status(
        struct ums_device_o *dev);

extern ums_time_t
ums_device_get_passed(
        struct ums_device_o *dev);

extern ums_time_t
ums_device_get_cycle(
        struct ums_device_o *dev);

extern struct ums_device_o *
ums_device_get_parent(
        struct ums_device_o *dev);

extern struct ums_list_o *
ums_device_get_childs(
        struct ums_device_o *dev);

extern void
ums_device_add(
        struct ums_device_o *dev,
        struct ums_device_o *to_add);

extern void
ums_device_remove(
        struct ums_device_o *dev,
        struct ums_device_o *to_remove);

/**
 * @brief
 * @details
 * @param dev
 * @param name
 * @param value
 * @return
 */
extern int
ums_device_get_property(
        struct ums_device_o *dev,
        const char *name,
        struct ums_value_o *value);

/**
 * @brief
 * @details
 * @param dev
 * @param name
 * @param value
 * @return
 */
extern int
ums_device_set_property(
        struct ums_device_o *dev,
        const char *name,
        struct ums_value_o *value);

/*******************************************************************************
 * sections : protected
 ******************************************************************************/

#ifdef _UMS_PROTECTED_

/**
 * @brief Constructor a device.
 * @details
 * @param self Pointer to object.
 * @param name Name of device.
 */
typedef void (*ums_device_make_f)(
        struct ums_device_o *bar,
        const char *name);

typedef void (*ums_device_reset_f)(
        struct ums_device_o *self);

typedef void (*ums_device_irq_f)(
        struct ums_device_o *self,
        int reason);

typedef void (*ums_device_change_f)(
        struct ums_device_o *self);

typedef void (*ums_device_add_f)(
        struct ums_device_o *self,
        struct ums_device_o *child);

typedef void (*ums_device_remove_f)(
        struct ums_device_o *self,
        struct ums_device_o *child);

typedef void (*ums_device_parent_report_f)(
        struct ums_device_o *self,
        struct ums_device_o *child);

typedef struct ums_device_o {
        ums_object_o super;

        const char *name;
        const char *label;
        int _id;
        ums_device_make_f _make;

        volatile int status;

        ums_device_reset_f reset_handler;
        ums_device_irq_f irq_handler;

        ums_time_t passed;
        ums_time_t coming;
        ums_time_t cycle;

        ums_device_change_f change_perform;
        ums_device_change_f change_latch;
        ums_device_change_f change_notify;

        struct ums_device_o *parent;
        struct ums_list_o childs;
        ums_device_add_f child_add;
        ums_device_remove_f child_remove;
        ums_device_parent_report_f send_parent_report;

        struct ums_list_o property;

        struct ums_signals_o signals;
} ums_device_o;

#endif /* _UMS_PROTECTED_ */

#endif /* CORE_DEVICE_H_ */
