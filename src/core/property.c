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

#include <string.h>

#define _UMS_PROTECTED_
#include <ums/core/property.h>
#undef _UMS_PROTECTED_

#include <ums/core/error.h>
#include "init.h"

static int
get_size(
        struct ums_property_o *self)
{
        int result;

        switch (self->type) {
        case TYPE_BYTE:
                result = sizeof(ums_byte_t);
                break;

        case TYPE_DWORD:
                result = sizeof(ums_dword_t);
                break;

        case TYPE_QWORD:
                result = sizeof(ums_qword_t);
                break;

        case TYPE_WORD:
                result = sizeof(ums_word_t);
                break;

        case TYPE_TIME:
                result = sizeof(ums_time_t);
                break;

        case TYPE_FLOAT:
                result = sizeof(ums_float_t);
                break;

        default:
                _FATAL("Unknown type.\n");
                result = -1;
        }

        return result;
}

ums_property_o *
ums_property_make(
        void *bar,
        const char *name,
        int type,
        void *holder,
        ums_property_get_size_f func_size,
        ums_property_getter_f func_get,
        ums_property_setter_f func_set)
{
        if (type == TYPE_BYTE_ARRAY && func_size == NULL) {
                _FATAL("In function ums_property_make(*bar, *name, type, *holder, func_size, "
                       "func_get, func_set) #func_size is NULL.\n");
                return NULL;
        }

        if (func_get == NULL) {
                _FATAL("In function ums_property_make(*bar, *name, type, *holder, func_size, "
                       "func_get, func_set) #func_get is NULL.\n");
                return NULL;
        }

        if (func_set == NULL) {
                _FATAL("In function ums_property_make(*bar, *name, type, *holder, func_size, "
                       "func_get, func_set) #func_set is NULL.\n");
                return NULL;
        }

        if (holder == NULL) {
                _FATAL("In function ums_property_make(*bar, *name, type, *holder, func_size, "
                       "func_get, func_set) #holder is NULL.\n");
                return NULL;
        }

        ums_property_o *result = ums_object_create(bar, &UMS_CLASS_PROPERTY, 0);
        result->name = name;
        result->type = type;
        result->holder = holder;
        result->getter = func_get;
        result->setter = func_set;

        if (type != TYPE_BYTE_ARRAY) {
                result->size_func = func_size;
        } else {
                result->size_func = get_size;
        }

        return result;
}

const char *
ums_property_name(
        ums_property_o *property)
{
        ums_property_o *prop = ums_object_cast(property, &UMS_CLASS_PROPERTY);

        if (prop == NULL) {
                _FATAL("In function ums_property_get_name(*property)"
                       " #property is NULL or is not belong to proper class.\n");
                return NULL;
        }

        return prop->name;
}

int
ums_property_type(
        ums_property_o *property)
{
        ums_property_o *prop = ums_object_cast(property, &UMS_CLASS_PROPERTY);

        if (prop == NULL) {
                _FATAL("In function ums_property_type(*property)"
                       " #property is NULL or is not belong to proper class.\n");
                return -1;
        }

        return prop->type;
}

size_t
ums_property_size(
        ums_property_o *property)
{
        ums_property_o *prop = ums_object_cast(property, &UMS_CLASS_PROPERTY);

        if (prop == NULL) {
                _FATAL("In function ums_property_size(*property)"
                       " #property is NULL or is not belong to proper class.\n");
                return 0;
        }

        return prop->size_func(prop);
}

int
ums_property_get(
        ums_property_o *property,
        ums_value_o *value)
{
        ums_property_o *prop = ums_object_cast(property, &UMS_CLASS_PROPERTY);

        if (prop == NULL) {
                _FATAL("In function ums_property_get(*property, *value)"
                       " #property is NULL or is not belong to proper class.\n");
                return -1;
        }

        ums_value_o *val = ums_object_cast(value, &UMS_CLASS_VALUE);

        if (val == NULL) {
                _FATAL("In function ums_property_get(*property, *value) #value is NULL "
                       "or is not belong to proper class.\n");
                return -1;
        }

        return prop->getter(prop, val);
}

int
ums_property_set(
        ums_property_o *property,
        ums_value_o *value)
{
        ums_property_o *prop = ums_object_cast(property, &UMS_CLASS_PROPERTY);

        if (prop == NULL) {
                _FATAL("In function ums_property_set(*property, *value)"
                       " #property is NULL or is not belong to proper class.\n");
                return -1;
        }

        ums_value_o *val = ums_object_cast(value, &UMS_CLASS_VALUE);

        if (val == NULL) {
                _FATAL("In function ums_property_set(*property, *value) #value is NULL "
                       "or is not belong to proper class.\n");
                return -1;
        }

        if (prop->type != ums_value_type(val)) {
                _ERROR("In function ums_property_set(*property, *value)"
                       " #value has not proper type.\n");
                return -1;
        }

        return prop->setter(prop, val);
}

/******************************************************************************
 * Inside class
 *****************************************************************************/

static void
init(
        ums_property_o *self,
        const void *init_data)
{
        UMS_CLASS_PROPERTY.super->init(&self->super, 0);
}

static void
destroy(
        ums_property_o *self)
{

        UMS_CLASS_PROPERTY.super->destroy(&self->super);
}

static int
compare(
        const ums_property_o *obj,
        const ums_property_o *cmp)
{
        return strcmp(obj->name, cmp->name);
}

const ums_class_t UMS_CLASS_PROPERTY = {
        .super = &UMS_CLASS_OBJECT,
        .object_size = sizeof(ums_property_o),
        .class_name = "UmsProperty",
        .init = (ums_class_init_f) init,
        .destroy = (ums_class_destroy_f) destroy,
        .compare = (ums_class_compare_f) compare,
        .copy = (ums_class_copy_f) 0
};
