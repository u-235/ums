/**
 * @file
 * @brief
 * @details
 *
 * @date создан 19.05.2019
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

#ifndef UMS_CORE_PROPERTY_H_
#define UMS_CORE_PROPERTY_H_

#include "object.h"
#include "value.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ums_property_o;
extern const struct ums_class_t UMS_CLASS_PROPERTY;

extern const char *
ums_property_name(
        struct ums_property_o *property);

extern int
ums_property_type(
        struct ums_property_o *property);

extern size_t
ums_property_size(
        struct ums_property_o *property);

extern int
ums_property_get(
        struct ums_property_o *property,
        struct ums_value_o *value);

extern int
ums_property_set(
        struct ums_property_o *property,
        struct ums_value_o *value);

typedef int (*ums_property_get_size_f)(
        struct ums_property_o *self);

typedef int (*ums_property_getter_f)(
        struct ums_property_o *self,
        struct ums_value_o *value);

typedef int (*ums_property_setter_f)(
        struct ums_property_o *self,
        struct ums_value_o *value);

/*******************************************************************************
 * sections : protected
 ******************************************************************************/

#ifdef _UMS_PROTECTED_

extern struct ums_property_o *
ums_property_make(
        void *bar,
        const char *name,
        int type,
        void *holder,
        ums_property_get_size_f func_size,
        ums_property_getter_f func_get,
        ums_property_setter_f func_set);

typedef struct ums_property_o {
        ums_object_o super;

        const char *name;
        int type;

        ums_object_o *holder;

        ums_property_get_size_f size_func;
        ums_property_getter_f getter;
        ums_property_setter_f setter;
} ums_property_o;

#endif /* _UMS_PROTECTED_ */

#ifdef __cplusplus
}
#endif

#endif /* UMS_CORE_PROPERTY_H_ */
