/**
 * @file
 * @brief
 * @details
 *
 * @date создан 12.06.2019
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

#define _UMS_PROTECTED_
#include <ums/core/signals.h>
#undef _UMS_PROTECTED_

#include <ums/core/error.h>
#include "init.h"

ums_signals_o *
ums_signals_make(
        void *bar)
{
        ums_signals_o *result;

        result = ums_object_create(bar, &UMS_CLASS_SIGNALS, 0);
        return result;
}

/******************************************************************************
 * Inside class
 *****************************************************************************/

static void
init(
        ums_signals_o *self,
        const void *init_data)
{
        UMS_CLASS_SIGNALS.super->init(&self->_super, 0);

        ums_list_make(&self->_aliases, &UMS_CLASS_SIGNALS_ALIAS);
        ums_list_make(&self->_recevers, &UMS_CLASS_SIGNALS_RECEIVER);
        ums_list_make(&self->_senders, &UMS_CLASS_SIGNALS_SENDER);
}

static void
destroy(
        ums_signals_o *self)
{
        ums_object_unlock(&self->_aliases);
        ums_object_unlock(&self->_recevers);
        ums_object_unlock(&self->_senders);

        UMS_CLASS_SIGNALS.super->destroy(&self->_super);
}

const ums_class_t UMS_CLASS_SIGNALS = {
        .super = &UMS_CLASS_OBJECT,
        .object_size = sizeof(ums_signals_o),
        .class_name = "UmsSignals",
        .init = (ums_class_init_f) init,
        .destroy = (ums_class_destroy_f) destroy
};
