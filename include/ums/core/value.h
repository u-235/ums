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

#ifndef UMS_CORE_VALUE_H_
#define UMS_CORE_VALUE_H_

#include <stddef.h>
#include "object.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ums_value_o;
extern const struct ums_class_t UMS_CLASS_VALUE;

extern struct ums_value_o *
ums_value_make(
        void *bar);

extern int
ums_value_type(
        struct ums_value_o *value);

extern size_t
ums_value_size(
        struct ums_value_o *value);

extern ums_byte_t
ums_value_get_byte(
        struct ums_value_o *value);

extern void
ums_value_set_byte(
        struct ums_value_o *value,
        ums_byte_t data);

extern ums_word_t
ums_value_get_word(
        struct ums_value_o *value);

extern void
ums_value_set_word(
        struct ums_value_o *value,
        ums_word_t data);

extern ums_dword_t
ums_value_get_dword(
        struct ums_value_o *value);

extern void
ums_value_set_dword(
        struct ums_value_o *value,
        ums_dword_t data);

extern ums_qword_t
ums_value_get_qword(
        struct ums_value_o *value);

extern void
ums_value_set_qword(
        struct ums_value_o *value,
        ums_qword_t data);

extern ums_float_t
ums_value_get_float(
        struct ums_value_o *value);

extern void
ums_value_set_float(
        struct ums_value_o *value,
        ums_float_t data);

extern void
ums_value_get_array(
        struct ums_value_o *value,
        void *data,
        size_t size);

extern void
ums_value_set_array(
        struct ums_value_o *value,
        void *data,
        size_t size);

/*******************************************************************************
 * sections : protected
 ******************************************************************************/

#ifdef _UMS_PROTECTED_

typedef struct ums_value_o {
        ums_object_o _super;

        int _type;
        size_t _size;
        union {
                ums_byte_t _byte;
                ums_word_t _word;
                ums_dword_t _dword;
                ums_qword_t _qword;
                ums_float_t _float;
                ums_byte_t *_array;
        };
} ums_value_o;

#endif /* _UMS_PROTECTED_ */

#ifdef __cplusplus
}
#endif

#endif /* UMS_CORE_VALUE_H_ */
