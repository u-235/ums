/**
 * @file
 * @brief
 * @details
 *
 * @date создан 13.06.2019 г.
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
#include <ums/core/signals.h>
#undef _UMS_PROTECTED_

#include <ums/core/error.h>
#include "init.h"

ums_signals_alias_o *
ums_signals_alias_make(
        void *bar,
        char *sender,
        char *receiver)
{
        ums_signals_alias_o *result;
        size_t s_size, r_size;

        if (sender == NULL || (s_size = strlen(sender)) == 0) {
                _FATAL("In function ums_signals_alias_make(bar, sender, receiver) #sender "
                       "is NULL.\n");
                return NULL;
        }

        if (receiver == NULL || (r_size = strlen(receiver)) == 0) {
                _FATAL("In function ums_signals_alias_make(bar, sender, receiver) #receiver "
                       "is NULL.\n");
                return NULL;
        }

        result = ums_object_create(bar, &UMS_CLASS_SIGNALS_ALIAS, 0);
        result->_sender = malloc(s_size + 1);

        if (result->_sender == NULL) {
                _FATAL("In function ums_signals_alias_make(bar, sender, receiver) can not "
                       "allocate memory.\n");
                return NULL;
        }

        result->_receiver = malloc(r_size + 1);

        if (result->_receiver == NULL) {
                _FATAL("In function ums_signals_alias_make(bar, sender, receiver) can not "
                       "allocate memory.\n");
                return NULL;
        }

        strcpy(result->_sender, sender);
        strcpy(result->_receiver, receiver);
        return result;
}

/******************************************************************************
 * Inside class
 *****************************************************************************/

static void
init(
        ums_signals_alias_o *self,
        const void *init_data)
{
        UMS_CLASS_SIGNALS_ALIAS.super->init(&self->_super, 0);
}

static void
destroy(
        ums_signals_alias_o *self)
{
        free(self->_receiver);
        free(self->_sender);

        UMS_CLASS_SIGNALS_ALIAS.super->destroy(&self->_super);
}

const ums_class_t UMS_CLASS_SIGNALS_ALIAS = {
        .super = &UMS_CLASS_OBJECT,
        .object_size = sizeof(ums_signals_alias_o),
        .class_name = "UmsSignalsAlias",
        .init = (ums_class_init_f) init,
        .destroy = (ums_class_destroy_f) destroy
};

