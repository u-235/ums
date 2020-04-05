/**
 * @file
 * @brief
 * @details
 *
 * @date создан 21.05.2019
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

#include <stdio.h>

#define _UMS_PROTECTED_
#include <ums/core/logger.h>
#include <ums/core/error.h>
#undef _UMS_PROTECTED_

#include "init.h"

static ums_logger_o core_logger;
static const char *core_error;

void
ums_error_set(
        const char *error)
{
        core_error = error;
}

extern void
ums_report(
        const int level,
        const char *file,
        const int line,
        const char *msg,
        ...)
{
        char *head;

        switch (level) {
        case LOG_DEBUG:
                head = "Debug message";
                break;

        case LOG_TRACE:
                head = "Trace message";
                break;

        case LOG_OUTPUT:
                head = "Output message";
                break;

        case LOG_WARNING:
                head = "Warning";
                break;

        case LOG_ERROR:
                head = "Error";
                ums_error_set(msg);
                break;

        case LOG_FATAL:
                head = "Fatal error";
                ums_error_set(msg);
                break;

        default:
                head = "?";
        }

        ums_logger_print(&core_logger, level, "\n%s in file %s, line %i.\n", head, file, line);
        va_list ap;
        va_start(ap, msg);
        ums_logger_vprint(&core_logger, level, msg, ap);
        va_end(ap);
}

const char *
ums_error_get(
        void)
{
        const char *result = core_error;
        core_error = NULL;
        return result;
}

struct ums_logger_o *
ums_error_get_logger(
        void)
{
        return &core_logger;
}

void
ums_error_init(
        void)
{
        ums_logger_make(&core_logger);
}

