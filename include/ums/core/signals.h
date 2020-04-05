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

#ifndef UMS_CORE_SIGNALS_H_
#define UMS_CORE_SIGNALS_H_

#include "list.h"
#include "object.h"
#include "types.h"
#include "value.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ums_signals_o;
extern const struct ums_class_t UMS_CLASS_SIGNALS;

struct ums_signals_sender_o;
extern const struct ums_class_t UMS_CLASS_SIGNALS_SENDER;

struct ums_signals_receiver_o;
extern const struct ums_class_t UMS_CLASS_SIGNALS_RECEIVER;

struct ums_signals_alias_o;
extern const struct ums_class_t UMS_CLASS_SIGNALS_ALIAS;

/*******************************************************************************
 * sections : protected
 ******************************************************************************/

#ifdef _UMS_PROTECTED_

typedef void (*ums_signal_f)(
        struct ums_signals_receiver_o *receiver,
        int value);

typedef struct ums_signals_sender_o {
        ums_object_o _super;

        char *_name;
        ums_qword_t _value;
        struct ums_list_o _recevers;
} ums_signals_sender_o;

typedef struct ums_signals_receiver_o {
        ums_object_o _super;

        char *_name;
        ums_signal_f _signal;
        ums_value_o _data;
} ums_signals_receiver_o;

typedef struct ums_signals_alias_o {
        ums_object_o _super;

        char *_sender;
        char *_receiver;
} ums_signals_alias_o;

extern ums_signals_alias_o *
ums_signals_alias_make(
        void *bar,
        char *sender,
        char *receiver);

typedef struct ums_signals_o {
        ums_object_o _super;

        struct ums_list_o _senders;
        struct ums_list_o _recevers;
        struct ums_list_o _aliases;
} ums_signals_o;

extern ums_signals_o *
ums_signals_make(
        void *bar);

#endif /* _UMS_PROTECTED_ */

#ifdef __cplusplus
}
#endif

#endif /* UMS_CORE_SIGNALS_H_ */
