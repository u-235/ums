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

#ifndef UMS_CORE_TYPES_H_
#define UMS_CORE_TYPES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t ums_byte_t;
typedef uint16_t ums_word_t;
typedef uint32_t ums_dword_t;
typedef uint64_t ums_qword_t;
typedef float ums_float_t;

typedef int64_t ums_time_t;
#define UMS_TIME_MAX INT64_MAX
#define UMS_TIME_MIN INT64_MIN

enum {
        TYPE_BYTE,
        TYPE_WORD,
        TYPE_DWORD,
        TYPE_QWORD,
        TYPE_TIME,
        TYPE_FLOAT,
        TYPE_BYTE_ARRAY
};

#ifdef __cplusplus
}
#endif

#endif /* UMS_CORE_TYPES_H_ */
