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

#include <stdlib.h>
#include <string.h>

#define _UMS_PROTECTED_
#include <ums/core/list.h>
#undef _UMS_PROTECTED_

#include <ums/core/error.h>
#include "init.h"

#ifndef UMS_LIST_GRANULARITY
        #define UMS_LIST_GRANULARITY 8
#endif

ums_list_o *
ums_list_make(
        ums_list_o *bar,
        const ums_class_t *iclass)
{
        ums_list_o *result = ums_object_create(bar, &UMS_CLASS_LIST, 0);
        result->items_class = iclass;
        return result;
}

const ums_class_t *
ums_list_items_class(
        ums_list_o *list)
{
        ums_list_o *l = ums_object_cast(list, &UMS_CLASS_LIST);

        if (l == NULL) {
                _FATAL("In function ums_list_items_class(*list) #list is NULL or "
                       "is not belong to proper class.\n");
                return NULL;
        }

        return l->items_class;
}

int
ums_list_lenght(
        ums_list_o *list)
{
        ums_list_o *l = ums_object_cast(list, &UMS_CLASS_LIST);

        if (l == NULL) {
                _FATAL("In function ums_list_lenght(*list) #list is NULL or "
                       "is not belong to proper class.\n");
                return -1;
        }

        return l->length;
}

int
ums_list_capacity(
        ums_list_o *list)
{
        ums_list_o *l = ums_object_cast(list, &UMS_CLASS_LIST);

        if (l == NULL) {
                _FATAL("In function ums_list_capacity(*list) #list is NULL or "
                       "is not belong to proper class.\n");
                return -1;
        }

        return l->capacity;
}

static int
get_index(
        ums_list_o *self,
        void *item)
{
        for (int i = 0; i < self->length; i++) {
                if (ums_object_compare(self->items[i], item) == 0) {
                        return i;
                }
        }

        return -1;
}

int
ums_list_index(
        ums_list_o *list,
        void *item)
{
        ums_list_o *l = ums_object_cast(list, &UMS_CLASS_LIST);

        if (l == NULL) {
                _FATAL("In function ums_list_index(*list, *item) #list is NULL or "
                       "is not belong to proper class.\n");
                return -1;
        }

        return get_index(list, item);
}

void *
ums_list_item(
        ums_list_o *list,
        size_t index)
{
        ums_list_o *l = ums_object_cast(list, &UMS_CLASS_LIST);

        if (l == NULL) {
                _FATAL("In function ums_list_item(*list, index) #list is NULL or "
                       "is not belong to proper class.\n");
                return NULL;
        }

        if (index >= l->length) {
                _ERROR("In function ums_list_item(*list, index) #index "
                       "greater than the list.\n");
                return NULL;
        }

        return l->items[index];
}

void
ums_list_iterate(
        struct ums_list_o *list,
        int (*handler)(void *item, void *data),
        void *data)
{
        ums_list_o *l = ums_object_cast(list, &UMS_CLASS_LIST);

        if (l == NULL) {
                _FATAL("In function ums_list_iterate(*list, *handler, *data) #list is NULL or "
                       "is not belong to proper class.\n");
        }

        int max = l->length;

        for (int i = 0; i < max; i++) {
                if (handler(l->items[i], data) == 0) {
                        break;
                }
        }
}

void **
ums_list_get_raw_deta(
        struct ums_list_o *list)
{
        ums_list_o *l = ums_object_cast(list, &UMS_CLASS_LIST);

        if (l == NULL) {
                _FATAL("In function ums_list_get_raw_deta(*list) #list is NULL or "
                       "is not belong to proper class.\n");
        }

        return l->items;
}

static int
request_memory(
        ums_list_o *list)
{
        if (list->length < list->capacity) {
                return 1;
        }

        void *new_mem = calloc(list->capacity + UMS_LIST_GRANULARITY, sizeof(void *));

        if (new_mem == NULL) {
                return 0;
        }

        memcpy(new_mem, list->items, list->length * sizeof(void *));
        free(list->items);
        list->items = new_mem;
        list->capacity += UMS_LIST_GRANULARITY;
        return 1;
}

extern int
ums_list_add(
        ums_list_o *list,
        void *to_add)
{
        ums_list_o *l = ums_object_cast(list, &UMS_CLASS_LIST);

        if (l == NULL) {
                _FATAL("In function ums_list_add(*list, *to_add) #list is NULL or "
                       "is not belong to proper class.\n");
                return -1;
        }

        ums_object_o *obj = ums_object_cast(to_add, l->items_class);

        if (obj == NULL) {
                _ERROR("In function ums_list_add(*list, *to_add) #to_add is NULL or "
                       "is not belong to proper class.\n");
                return -1;
        }

        if (get_index(l, obj) >= 0) {
                _WARNING("In function ums_list_add(*list, *to_add) #to_add always in list.\n");
                return -1;
        }

        if (request_memory(l) == 0) {
                _FATAL("Can't allocate memory in function ums_list_add(*list, *to_add).\n");
                return -1;
        }

        l->items[l->length++] = obj;
        ums_object_lock(obj);

        return l->length;
}

extern int
ums_list_remove(
        ums_list_o *list,
        void *to_remove)
{
        ums_list_o *l = ums_object_cast(list, &UMS_CLASS_LIST);

        if (l == NULL) {
                _FATAL("In function ums_list_remove(*list, *to_remove) #list is NULL or "
                       "is not belong to proper class.\n");
                return -1;
        }

        int index = get_index(l, to_remove);

        if (index < 0) {
                _ERROR("In function ums_list_remove(*list, *to_remove) #to_remove "
                       "is not belong to list.\n");
                return -1;
        }

        ums_object_unlock(l->items[index]);
        l->items[index] = 0;
        memcpy(&l->items[index], &l->items[index + 1],
               (l->length - index + 1) * sizeof(void *));
        l->length--;
        /* TODO reduce size of _items */
        return index;
}

static void
remove_all(
        ums_list_o *self)
{
        for (int i = 0; i < self->length; i++) {
                ums_object_unlock(self->items[i]);
                self->items[i] = 0;
        }

        self->length = 0;

        return;
}

extern void
ums_list_remove_all(
        ums_list_o *list)
{
        ums_list_o *l = ums_object_cast(list, &UMS_CLASS_LIST);

        if (l == NULL) {
                _FATAL("In function ums_list_remove_all(*list) #list is NULL or "
                       "is not belong to proper class.\n");
                return;
        }

        remove_all(l);
        /* TODO reduce size of _items */
        return;
}

/******************************************************************************
 * Inside class
 *****************************************************************************/

static void
init(
        ums_list_o *self,
        const void *init_data)
{
        UMS_CLASS_LIST.super->init(&self->super, 0);
        self->length = 0;
        self->capacity = 0;
        request_memory(self);
}

static void
destroy(
        ums_list_o *self)
{
        remove_all(self);
        free(self->items);
        UMS_CLASS_LIST.super->destroy(&self->super);
}

const ums_class_t UMS_CLASS_LIST = {
        .super = &UMS_CLASS_OBJECT,
        .object_size = sizeof(ums_list_o),
        .class_name = "UmsList",
        .init = (ums_class_init_f) init,
        .destroy = (ums_class_destroy_f) destroy
};
