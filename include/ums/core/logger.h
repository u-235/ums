/**
 * @file
 * @brief
 * @details
 *
 * @date создан 12.04.2019
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

#ifndef UMS_CORE_LOGGER_H_
#define UMS_CORE_LOGGER_H_

#include <stdarg.h>
#include "object.h"

struct ums_logger_o;
extern const struct ums_class_t UMS_LOGGER_CLASS;

enum {
        LOG_NONE = 0,
        LOG_FATAL,
        LOG_ERROR,
        LOG_WARNING,
        LOG_OUTPUT,
        LOG_TRACE,
        LOG_DEBUG
};

extern void
ums_logger_vprint(
        const struct ums_logger_o *log,
        const int level,
        const char *format,
        va_list ap);

extern void
ums_logger_print(
        const struct ums_logger_o *log,
        const int level,
        const char *format,
        ...);

extern void
ums_logger_set_level(
        struct ums_logger_o *log,
        int level);

extern int
ums_logger_get_level(
        const struct ums_logger_o *log);

typedef void (*log_func)(
        const struct ums_logger_o *log,
        const int level,
        const char *format,
        va_list ap);

extern void
ums_logger_set(
        struct ums_logger_o *log,
        log_func logger);

extern log_func
ums_logger_get(
        const struct ums_logger_o *log);

extern struct ums_logger_o *
ums_logger_make(
        struct ums_logger_o *logger);

/*******************************************************************************
 * sections : protected
 ******************************************************************************/

#ifdef _UMS_PROTECTED_

typedef struct ums_logger_o {
        ums_object_o super;

        int log_level;
        log_func log_func;
} ums_logger_o;

#endif /* _UMS_PROTECTED_ */

#endif /* UMS_CORE_LOGGER_H_ */
