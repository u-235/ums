/**
 * @file
 * @brief
 * @details
 *
 * @date создан 4.05.2019
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
#include <ums/core/device.h>
#undef _UMS_PROTECTED_

#include <ums/core/error.h>
#include "init.h"

const char *
ums_device_get_name(
        ums_device_o *dev)
{
        ums_device_o *d = ums_object_cast(dev, &UMS_CLASS_DEVICE);

        if (d == NULL) {
                _FATAL("In function ums_device_get_name(dev) #dev is NULL or is not belong"
                       " to proper class.\n");
                return NULL;
        }

        return d->name;
}

extern void
ums_device_set_label(
        ums_device_o *dev,
        const char *label)
{
        ums_device_o *d = ums_object_cast(dev, &UMS_CLASS_DEVICE);

        if (d == NULL) {
                _FATAL("In function ums_device_set_label(*dev, *label) #label is NULL or"
                       " is not belong to proper class.\n");
                return;
        }

        d->label = label;
}

extern const char *
ums_device_get_label(
        ums_device_o *dev)
{
        ums_device_o *d = ums_object_cast(dev, &UMS_CLASS_DEVICE);

        if (d == NULL) {
                _FATAL("In function ums_device_get_label(dev) #dev is NULL or is not belong"
                       " to proper class.\n");
                return NULL;
        }

        return d->label;
}

int
ums_device_get_id(
        ums_device_o *dev)
{
        ums_device_o *d = ums_object_cast(dev, &UMS_CLASS_DEVICE);

        if (d == NULL) {
                _FATAL("In function ums_device_get_id(dev) #dev is NULL or is not belong"
                       " to proper class.\n");
                return -1;
        }

        return d->_id;
}

int
ums_device_status(
        ums_device_o *dev)
{
        ums_device_o *d = ums_object_cast(dev, &UMS_CLASS_DEVICE);

        if (d == NULL) {
                _FATAL("In function ums_device_status(dev) #dev is NULL or is not belong"
                       " to proper class.\n");
                return -1;
        }

        return d->status;
}

ums_time_t
ums_device_get_passed(
        ums_device_o *dev)
{
        ums_device_o *d = ums_object_cast(dev, &UMS_CLASS_DEVICE);

        if (d == NULL) {
                _FATAL("In function ums_device_get_passed(dev) #dev is NULL or is not belong"
                       " to proper class.\n");
                return 0;
        }

        return d->passed;
}

ums_time_t
ums_device_get_cycle(
        ums_device_o *dev)
{
        ums_device_o *d = ums_object_cast(dev, &UMS_CLASS_DEVICE);

        if (d == NULL) {
                _FATAL("In function ums_device_get_cycle(dev) #dev is NULL or is not belong"
                       " to proper class.\n");
                return 0;
        }

        return dev->cycle;
}

ums_device_o *
ums_device_get_parent(
        ums_device_o *dev)
{
        ums_device_o *d = ums_object_cast(dev, &UMS_CLASS_DEVICE);

        if (d == NULL) {
                _FATAL("In function ums_device_get_parent(dev) #dev is NULL or is not belong"
                       " to proper class.\n");
                return NULL;
        }

        return d->parent;
}

ums_list_o *
ums_device_get_childs(
        ums_device_o *dev)
{
        ums_device_o *d = ums_object_cast(dev, &UMS_CLASS_DEVICE);

        if (d == NULL) {
                _FATAL("In function ums_device_get_child(dev) #dev is NULL or is not belong"
                       " to proper class.\n");
                return 0;
        }

        return &d->childs;
}

void
ums_device_add(
        ums_device_o *dev,
        ums_device_o *added)
{
        ums_device_o *d = ums_object_cast(dev, &UMS_CLASS_DEVICE);

        if (d == NULL) {
                _FATAL("In function ums_device_add(dev, toAdd) #dev is NULL or is not belong"
                       " to proper class.\n");
                return;
        }

        added = ums_object_cast(added, &UMS_CLASS_DEVICE);

        if (added == NULL) {
                _ERROR("In function ums_device_add(dev, toAdd) #toAdd is NULL.\n");
                return;
        }

        d->child_add(d, added);
}

void
ums_device_remove(
        ums_device_o *dev,
        ums_device_o *removed)
{
        ums_device_o *d = ums_object_cast(dev, &UMS_CLASS_DEVICE);

        if (d == NULL) {
                _FATAL("In function ums_device_remove(dev) #dev is NULL or is not belong"
                       " to proper class.\n");
                return;
        }

        removed = ums_object_cast(removed, &UMS_CLASS_DEVICE);

        if (removed == NULL) {
                _ERROR("In function ums_device_remove(dev, toRemove) #toRemove is NULL.\n");
                return;
        }

        d->child_remove(d, removed);
}

struct find_data {
        const char *_name;
        struct ums_property_o *_result;
};

static int
find_handler(void *item, void *data)
{
        struct find_data *d = data;
        int cmp = strcmp(ums_property_name(item), d->_name);

        if (cmp == 0) {
                d->_result = item;
        }

        return cmp;
}

static struct ums_property_o *
find_property(
        ums_device_o *dev,
        const char *name)
{
        struct find_data d;
        d._name = name;
        d._result = NULL;
        ums_list_iterate(&dev->property, find_handler, &d);
        return d._result;
}

int
ums_device_set_property(
        ums_device_o *dev,
        const char *name,
        ums_value_o *value)
{
        ums_device_o *d = ums_object_cast(dev, &UMS_CLASS_DEVICE);

        if (d == NULL) {
                _FATAL("In function ums_device_set_property(dev, name, value) #dev is NULL "
                       "or is not belong to proper class.\n");
                return -1;
        }

        if (name == NULL) {
                _FATAL("In function ums_device_set_property(dev, name, value) #name "
                       "is NULL.\n");
                return -1;
        }

        if (value == NULL) {
                _FATAL("In function ums_device_set_property(dev, name, value) #value "
                       "is NULL.\n");
                return -1;
        }

        struct ums_property_o *prop = find_property(d, name);

        if (prop == NULL || ums_property_type(prop) != ums_value_type(value)) {
                _ERROR("In function ums_device_set_property(dev, name, value) property"
                       " not found.\n");
                return -1;
        }

        return ums_property_set(prop, value);
}

int
ums_device_get_property(
        ums_device_o *dev,
        const char *name,
        ums_value_o *value)
{
        ums_device_o *d = ums_object_cast(dev, &UMS_CLASS_DEVICE);

        if (d == NULL) {
                _FATAL("In function ums_device_get_property(dev, name, value) #dev is NULL "
                       "or is not belong to proper class.\n");
                return -1;
        }

        if (name == NULL) {
                _FATAL("In function ums_device_get_property(dev, name, value) #name "
                       "is NULL.\n");
                return -1;
        }

        if (value == NULL) {
                _FATAL("In function ums_device_get_property(dev, name, value) #value "
                       "is NULL.\n");
                return -1;
        }

        struct ums_property_o *prop = find_property(d, name);

        return prop == NULL ? -1 : ums_property_get(prop, value);
}

/******************************************************************************
 * Virtual methods
 *****************************************************************************/

static int dev_count;

static void
make(
        ums_device_o *bar,
        const char *name)
{
        bar->name = name;
        bar->_id = dev_count++;
}

static void
reset(
        ums_device_o *self)
{
        self->passed = 0;
        self->cycle = 0;
        self->status = DEVICE_OK;
}

static void
irq(
        ums_device_o *self,
        int reason)
{
        if (self->parent != NULL) {
                self->parent->irq_handler(self->parent, reason);
        }
}

static void
add_child(
        ums_device_o *self,
        ums_device_o *child)
{
        if (child->parent != NULL) {
                _ERROR("In function add_child(self, child) #child already has parent.\n");
                return;
        }

        ums_list_add(&self->childs, child);
        child->parent = self;
        self->send_parent_report(self, child);
}

static void
remove_child(
        ums_device_o *self,
        ums_device_o *child)
{
        if (ums_list_index(&self->childs, child) < 0) {
                _ERROR("In function remove_child(self, child) #child not found.\n");
                return;
        }

        ums_list_remove(&self->childs, child);
}

static void
changed_child(
        ums_device_o *self,
        ums_device_o *child)
{
        ums_device_o *parent = ums_device_get_parent(self);

        if (parent != NULL) {
                parent->send_parent_report(parent, child);
        }
}

/******************************************************************************
 * Inside class
 *****************************************************************************/

static void
init(
        ums_device_o *self,
        const void *init_data)
{
        UMS_CLASS_DEVICE.super->init(&self->super, 0);

        self->_make = make;
        self->reset_handler = reset;
        self->irq_handler = irq;
        self->coming = UMS_TIME_MAX;
        self->passed = 0;
        self->change_perform = 0;
        self->change_latch = 0;
        self->change_notify = 0;
        self->child_add = add_child;
        self->child_remove = remove_child;
        self->send_parent_report = changed_child;
        ums_list_make(&self->childs, &UMS_CLASS_DEVICE);
        ums_list_make(&self->property, &UMS_CLASS_PROPERTY);
        ums_signals_make(&self->signals);
}

static void
destroy(
        ums_device_o *self)
{
        for (int i = ums_list_lenght(&self->childs) - 1; i >= 0; i--) {
                ums_device_o *child = ums_list_item(&self->childs, i);
                self->child_remove(self, child);
        }

        ums_object_unlock(&self->childs);
        ums_object_unlock(&self->property);
        ums_object_unlock(&self->signals);

        UMS_CLASS_DEVICE.super->destroy(&self->super);
}

const ums_class_t UMS_CLASS_DEVICE = {
        .super = &UMS_CLASS_OBJECT,
        .object_size = sizeof(ums_device_o),
        .class_name = "UmsDevice",
        .init = (ums_class_init_f) init,
        .destroy = (ums_class_destroy_f) destroy
};
