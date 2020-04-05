/**
 * @file
 * @brief
 * @details
 *
 * @date создан 16.05.2019
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
#include <ums/core/builder.h>
#undef _UMS_PROTECTED_

#include <ums/core/error.h>
#include "init.h"

static struct ums_device_o *
build(
        const char *name)
{
        struct ums_device_o *result = NULL;

        if (strstr(name, "_test_") == name) {
                result = (struct ums_device_o *) ums_object_create(0, &UMS_CLASS_DEVICE, 0);

                if (result != NULL) {
                        result->_make(result, name);
                }
        }

        return result;
}

static ums_builder_t test = {
        ._build = build,
        ._next = 0
};

static ums_builder_t *first;

extern void
ums_builder_add(
        ums_builder_t *builder)
{
        ums_builder_t **last = &first;

        while (*last != NULL) {
                last = &(*last)->_next;
        }

        *last = builder;
}

/*
 * TODO ums_builder_remove()
 */

extern ums_device_o *
ums_build(
        const char *name)
{
        ums_device_o *result = NULL;
        ums_builder_t *builder = first;

        while (builder != NULL) {
                result = builder->_build(name);

                if (result != NULL) {
                        break;
                }

                builder = builder->_next;
        }

        return result;
}

void
ums_builder_init(
        void)
{
        ums_builder_add(&test);
}

