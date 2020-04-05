/**
 * @file
 * @brief
 * @details
 *
 * @date создан 5.05.2019
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
#undef _UMS_PROTECTED_

static void
default_logger(
        const struct ums_logger_o *log,
        const int level,
        const char *format,
        va_list ap)
{
        if (log->log_level < level) {
                return;
        }

        vfprintf(level <= LOG_ERROR ? stderr : stdout, format, ap);
}

ums_logger_o *
ums_logger_make(
        ums_logger_o *log)
{
        ums_logger_o *result;
        result = ums_object_create(&log->super, &UMS_LOGGER_CLASS, 0);
        return result;
}

void
ums_logger_vprint(
        const ums_logger_o *log,
        const int level,
        const char *format,
        va_list ap)
{
        log->log_func(log, level, format, ap);
}

void
ums_logger_print(
        const ums_logger_o *log,
        const int level,
        const char *format,
        ...)
{
        va_list ap;
        va_start(ap, format);
        log->log_func(log, level, format, ap);
        va_end(ap);
}

void
ums_logger_set_level(
        ums_logger_o *log,
        int level)
{
        log->log_level = level;
}

int
ums_logger_get_level(
        const ums_logger_o *log)
{
        return log->log_level;

}

void
ums_logger_set(
        ums_logger_o *log,
        log_func logger)
{
        log->log_func = logger == NULL ? default_logger : logger;
}

log_func
ums_logger_get(
        const ums_logger_o *log)
{
        return log->log_func;
}

/******************************************************************************
 * Inside class
 *****************************************************************************/

static void
init(
        ums_logger_o *self,
        const void *init_data)
{
        UMS_LOGGER_CLASS.super->init(&self->super, 0);
        ums_logger_set(self, NULL);
}

static void
destroy(
        ums_logger_o *self)
{
        self->log_level = 0;
        UMS_LOGGER_CLASS.super->destroy(&self->super);
}

const ums_class_t UMS_LOGGER_CLASS = {
        .super = &UMS_CLASS_OBJECT,
        .object_size = sizeof(ums_logger_o),
        .class_name = "UmsLogger",
        .init = (void *) init,
        .destroy = (void *) destroy
};
