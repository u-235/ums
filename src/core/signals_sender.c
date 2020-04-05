/**
 * @file
 * @brief
 * @details
 *
 * @date создан 13.06.2019
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

/******************************************************************************
 * Inside class
 *****************************************************************************/

static void
init(
        ums_signals_sender_o *self,
        const void *init_data)
{
        UMS_CLASS_SIGNALS_SENDER.super->init(&self->_super, 0);
}

static void
destroy(
        ums_signals_sender_o *self)
{

        UMS_CLASS_SIGNALS_SENDER.super->destroy(&self->_super);
}

const ums_class_t UMS_CLASS_SIGNALS_SENDER = {
        .super = &UMS_CLASS_OBJECT,
        .object_size = sizeof(ums_signals_sender_o),
        .class_name = "UmsSignalsSender",
        .init = (ums_class_init_f) init,
        .destroy = (ums_class_destroy_f) destroy
};

