/**
 * @file
 * @brief
 * @details
 *
 * @date создан 10.06.2019
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

#include <malloc.h>
#include <string.h>

#define _UMS_PROTECTED_
#include <ums/core/value.h>
#undef _UMS_PROTECTED_

#include <ums/core/error.h>

ums_value_o *
ums_value_make(
        void *bar)
{
        ums_value_o *result = ums_object_create(bar, &UMS_CLASS_VALUE, 0);
        return result;
}

int
ums_value_type(
        ums_value_o *value)
{
        ums_value_o *v = ums_object_cast(value, &UMS_CLASS_VALUE);

        if (v == NULL) {
                _FATAL("In function ums_value_type(*value)"
                       " #value is NULL or is not belong to proper class.\n");
                return 0;
        }

        return v->_type;
}

size_t
ums_value_size(
        ums_value_o *value)
{
        ums_value_o *v = ums_object_cast(value, &UMS_CLASS_VALUE);

        if (v == NULL) {
                _FATAL("In function ums_value_size(*value)"
                       " #value is NULL or is not belong to proper class.\n");
                return 0;
        }

        return v->_size;
}

static int
prepare_value(
        ums_value_o *value,
        int type,
        size_t alloc)
{
        value->_size = 0;

        if (value->_type == TYPE_BYTE_ARRAY) {
                free(value->_array);
        } else {
                value->_qword = 0;
        }

        switch (type) {
        case TYPE_BYTE_ARRAY:
                value->_array = calloc(alloc, 1);
                value->_type = TYPE_BYTE_ARRAY;

                if (value->_array != NULL) {
                        value->_size = alloc;
                }

                break;

        case TYPE_BYTE:
                value->_type = TYPE_BYTE;
                value->_size = sizeof(ums_byte_t);
                break;

        case TYPE_DWORD:
                value->_type = TYPE_DWORD;
                value->_size = sizeof(ums_dword_t);
                break;

        case TYPE_QWORD:
                value->_type = TYPE_QWORD;
                value->_size = sizeof(ums_qword_t);
                break;

        case TYPE_WORD:
                value->_type = TYPE_WORD;
                value->_size = sizeof(ums_word_t);
                break;

        case TYPE_TIME:
                value->_type = TYPE_TIME;
                value->_size = sizeof(ums_time_t);
                break;

        case TYPE_FLOAT:
                value->_type = TYPE_FLOAT;
                value->_size = sizeof(ums_float_t);
                break;
        }

        return value->_size;
}

ums_byte_t
ums_value_get_byte(
        ums_value_o *value)
{
        ums_value_o *v = ums_object_cast(value, &UMS_CLASS_VALUE);

        if (v == NULL) {
                _FATAL("In function ums_value_get_byte(*value)"
                       " #value is NULL or is not belong to proper class.\n");
                return 0;
        }

        if (v->_type != TYPE_BYTE) {
                _FATAL("In function ums_value_get_byte(*value) #value "
                       "contains not proper type.\n");
                return 0;
        }

        return v->_byte;
}

void
ums_value_set_byte(
        ums_value_o *value,
        ums_byte_t data)
{
        ums_value_o *v = ums_object_cast(value, &UMS_CLASS_VALUE);

        if (v == NULL) {
                _FATAL("In function ums_value_set_byte(*value, data)"
                       " #value is NULL or is not belong to proper class.\n");
                return;
        }

        prepare_value(v, TYPE_BYTE, 0);
        v->_byte = data;
        return;
}

ums_word_t
ums_value_get_word(
        ums_value_o *value)
{
        ums_value_o *v = ums_object_cast(value, &UMS_CLASS_VALUE);

        if (v == NULL) {
                _FATAL("In function ums_value_get_word(*value)"
                       " #value is NULL or is not belong to proper class.\n");
                return 0;
        }

        if (v->_type != TYPE_WORD) {
                _FATAL("In function ums_value_get_word(*value) #value "
                       "contains not proper type.\n");
                return 0;
        }

        return v->_word;
}

void
ums_value_set_word(
        ums_value_o *value,
        ums_word_t data)
{
        ums_value_o *v = ums_object_cast(value, &UMS_CLASS_VALUE);

        if (v == NULL) {
                _FATAL("In function ums_value_set_word(*value, data)"
                       " #value is NULL or is not belong to proper class.\n");
                return;
        }

        prepare_value(v, TYPE_WORD, 0);
        v->_word = data;
        return;
}

ums_dword_t
ums_value_get_dword(
        ums_value_o *value)
{
        ums_value_o *v = ums_object_cast(value, &UMS_CLASS_VALUE);

        if (v == NULL) {
                _FATAL("In function ums_value_get_dword(*value)"
                       " #value is NULL or is not belong to proper class.\n");
                return 0;
        }

        if (v->_type != TYPE_DWORD) {
                _FATAL("In function ums_value_get_dword(*value) #value "
                       "contains not proper type.\n");
                return 0;
        }

        return v->_dword;
}

void
ums_value_set_dword(
        ums_value_o *value,
        ums_dword_t data)
{
        ums_value_o *v = ums_object_cast(value, &UMS_CLASS_VALUE);

        if (v == NULL) {
                _FATAL("In function ums_value_set_dword(*value, data)"
                       " #value is NULL or is not belong to proper class.\n");
                return;
        }

        prepare_value(v, TYPE_DWORD, 0);
        v->_dword = data;
        return;
}

ums_qword_t
ums_value_get_qword(
        ums_value_o *value)
{
        ums_value_o *v = ums_object_cast(value, &UMS_CLASS_VALUE);

        if (v == NULL) {
                _FATAL("In function ums_value_get_qword(*value)"
                       " #value is NULL or is not belong to proper class.\n");
                return 0;
        }

        if (v->_type != TYPE_QWORD) {
                _FATAL("In function ums_value_get_qword(*value) #value "
                       "contains not proper type.\n");
                return 0;
        }

        return v->_qword;
}

void
ums_value_set_qword(
        ums_value_o *value,
        ums_qword_t data)
{
        ums_value_o *v = ums_object_cast(value, &UMS_CLASS_VALUE);

        if (v == NULL) {
                _FATAL("In function ums_value_set_qword(*value, data)"
                       " #value is NULL or is not belong to proper class.\n");
                return;
        }

        prepare_value(v, TYPE_QWORD, 0);
        v->_qword = data;
        return;
}

ums_float_t
ums_value_get_float(
        ums_value_o *value)
{
        ums_value_o *v = ums_object_cast(value, &UMS_CLASS_VALUE);

        if (v == NULL) {
                _FATAL("In function ums_value_get_float(*value)"
                       " #value is NULL or is not belong to proper class.\n");
                return 0;
        }

        if (v->_type != TYPE_FLOAT) {
                _FATAL("In function ums_value_get_float(*value) #value "
                       "contains not proper type.\n");
                return 0;
        }

        return v->_float;
}

void
ums_value_set_float(
        ums_value_o *value,
        ums_float_t data)
{
        ums_value_o *v = ums_object_cast(value, &UMS_CLASS_VALUE);

        if (v == NULL) {
                _FATAL("In function ums_value_set_float(*value, data)"
                       " #value is NULL or is not belong to proper class.\n");
                return;
        }

        prepare_value(v, TYPE_FLOAT, 0);
        v->_float = data;
        return;
}

void
ums_value_get_array(
        ums_value_o *value,
        void *data,
        size_t size)
{
        ums_value_o *v = ums_object_cast(value, &UMS_CLASS_VALUE);

        if (v == NULL) {
                _FATAL("In function ums_value_get_array(*value, *data, size)"
                       " #value is NULL or is not belong to proper class.\n");
                return;
        }

        if (v->_type != TYPE_WORD) {
                _FATAL("In function ums_value_get_array(*value, *data, size) #value "
                       "contains not proper type.\n");
                return;
        }

        size_t s = size;

        if (s < v->_size) {
                _ERROR("In function ums_value_get_array(*value, *data, size) size of "
                       "#data less then size of array in #value.\n");
                s = v->_size;
        }

        memcpy(data, value->_array, s);
        return;
}

void
ums_value_set_array(
        ums_value_o *value,
        void *data,
        size_t size)
{
        ums_value_o *v = ums_object_cast(value, &UMS_CLASS_VALUE);

        if (v == NULL) {
                _FATAL("In function ums_value_set_array(*value, *data, size) "
                       "#value is NULL or is not belong to proper class.\n");
                return;
        }

        if (prepare_value(v, TYPE_BYTE_ARRAY, size) == 0) {
                _FATAL("In function ums_value_set_array(*value, data, size) "
                       "can not allocate array.\n");
                return;
        }

        memcpy(value->_array, data, size);
        return;
}

/******************************************************************************
 * Inside class
 *****************************************************************************/

#define SUPER_CLASS UMS_CLASS_OBJECT
#define THIS_CLASS  UMS_CLASS_VALUE

static void
init(
        ums_value_o *self,
        const void *init_data)
{
        THIS_CLASS.super->init(&self->_super, 0);
        self->_type = TYPE_QWORD;
        self->_qword = 0;
}

static void
destroy(
        ums_value_o *self)
{
        if (self->_type == TYPE_BYTE_ARRAY) {
                free(self->_array);
        }

        THIS_CLASS.super->destroy(&self->_super);
}

static int
compare(
        const ums_value_o *obj,
        const ums_value_o *cmp)
{
        return SUPER_CLASS.compare((ums_object_o *) obj, (ums_object_o *) cmp);
}

const ums_class_t THIS_CLASS = {
        .super = &SUPER_CLASS,
        .object_size = sizeof(ums_value_o),
        .class_name = "UmsValue",
        .init = (ums_class_init_f) init,
        .destroy = (ums_class_destroy_f) destroy,
        .compare = (ums_class_compare_f) compare,
        .copy = (ums_class_copy_f) 0
};
