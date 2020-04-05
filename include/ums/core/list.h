/**
 * @file
 * @brief
 * @details
 *
 * @date создан 25.05.2019
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

#ifndef UMS_CORE_LIST_H_
#define UMS_CORE_LIST_H_

#include <stddef.h>
#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ums_list_o;
extern const struct ums_class_t UMS_CLASS_LIST;

extern const struct ums_class_t *
ums_list_items_class(
        struct ums_list_o *list);

extern int
ums_list_lenght(
        struct ums_list_o *list);

extern int
ums_list_capacity(
        struct ums_list_o *list);

extern int
ums_list_index(
        struct ums_list_o *list,
        void *item);

extern void *
ums_list_item(
        struct ums_list_o *list,
        size_t index);

extern void
ums_list_iterate(
        struct ums_list_o *list,
        int (*handler)(void *item, void *data),
        void *data);

extern void **
ums_list_get_raw_deta(
        struct ums_list_o *list);

extern int
ums_list_add(
        struct ums_list_o *list,
        void *to_add);

extern int
ums_list_remove(
        struct ums_list_o *list,
        void *to_remove);

extern void
ums_list_remove_all(
        struct ums_list_o *list);

extern struct ums_list_o *
ums_list_make(
        struct ums_list_o *bar,
        const struct ums_class_t *iclass);

/*******************************************************************************
 * sections : protected
 ******************************************************************************/

#ifdef _UMS_PROTECTED_

typedef struct ums_list_o {
        struct ums_object_o super;

        void **items;
        const struct ums_class_t *items_class;
        size_t length;
        size_t capacity;
} ums_list_o;

#endif /* _UMS_PROTECTED_ */

#ifdef __cplusplus
}
#endif

#endif /* UMS_CORE_LIST_H_ */
