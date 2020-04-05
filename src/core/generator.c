/**
 * @file
 * @brief
 * @details
 *
 * @date создан 2.06.2019
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
#include <ums/core/generator.h>
#include <ums/core/builder.h>
#undef _UMS_PROTECTED_

#include <ums/core/error.h>

static void
calc_comming(
        struct ums_generator_o *self)
{
        if (self->period != 0) {
                self->super.coming = self->super.passed + self->period;
        } else if (self->freq != 0) {
                if (self->ticks == self->freq) {
                        self->ticks = 0;
                        self->base += 1000000000ULL;
                }

                self->super.coming = self->base
                                     + 1000000000ULL * (self->ticks + 1) / self->freq;
        } else {
                self->super.irq_handler(&self->super, DEVICE_ERROR_OUT_OF_RANGE);
        }
}

static int
get_period(
        struct ums_property_o *self,
        struct ums_value_o *value)
{
        struct ums_generator_o *gen = ums_object_cast(self->holder, &UMS_CLASS_GENERATOR);

        if (gen->period != 0) {
                value->_qword = gen->period;
        } else {
                value->_qword = 1000000000ULL / gen->freq;
        }

        return 0;
}

static int
set_period(
        struct ums_property_o *self,
        struct ums_value_o *value)
{
        struct ums_generator_o *gen = ums_object_cast(self->holder, &UMS_CLASS_GENERATOR);
        gen->period = ums_value_get_qword(value);
        gen->freq = 0;
        calc_comming(gen);
        return 0;
}

static int
get_freq(
        struct ums_property_o *self,
        struct ums_value_o *value)
{
        struct ums_generator_o *gen = ums_object_cast(self->holder, &UMS_CLASS_GENERATOR);

        if (gen->freq != 0) {
                value->_dword = gen->freq;
        } else {
                value->_dword = 1000000000ULL / gen->period;
        }

        return 0;
}

static int
set_freq(
        struct ums_property_o *self,
        struct ums_value_o *value)
{
        struct ums_generator_o *gen = ums_object_cast(self->holder, &UMS_CLASS_GENERATOR);
        gen->freq = ums_value_get_dword(value);
        gen->period = 0;
        calc_comming(gen);
        return 0;
}

static struct ums_device_o *
build(
        const char *name)
{
        struct ums_device_o *result = NULL;

        if (strcmp(name, "generator") == 0) {
                result = (ums_device_o *) ums_object_create(0, &UMS_CLASS_GENERATOR, 0);

                if (result != NULL) {
                        result->_make(result, name);
                }
        }

        return result;
}

static ums_builder_t builder = {
        ._build = build,
        ._next = 0
};

/******************************************************************************
 * Virtual methods
 *****************************************************************************/

static void
reset(
        struct ums_generator_o *self)
{
        self->override.reset(&self->super);
        self->base = 0;
        self->ticks = 0;
        calc_comming(self);
}

static void
perform(
        struct ums_generator_o *self)
{
        self->flags = 1;
}

static void
latch(
        struct ums_generator_o *self)
{
        if (self->flags == 0) {
                return;
        }

        self->flags = 0;
        self->ticks++;
        calc_comming(self);
        return;
}

/******************************************************************************
 * Inside class
 *****************************************************************************/

static void
init(
        struct ums_generator_o *self,
        const void *init_data)
{
        UMS_CLASS_GENERATOR.super->init(&self->super.super, init_data);
        struct ums_property_o *prop;
        prop = ums_property_make(NULL, "period", TYPE_QWORD, self, NULL, get_period,
                                 set_period);
        ums_list_add(&self->super.property, prop);
        ums_object_unlock(prop);

        prop = ums_property_make(NULL, "frequency", TYPE_DWORD, self, NULL, get_freq,
                                 set_freq);
        ums_list_add(&self->super.property, prop);
        ums_object_unlock(prop);
        self->override.reset = self->super.reset_handler;
        self->super.reset_handler = (ums_device_reset_f) reset;
        self->super.change_perform = (ums_device_change_f) perform;
        self->super.change_latch = (ums_device_change_f) latch;
}

static void
destroy(
        struct ums_generator_o *self)
{
        UMS_CLASS_GENERATOR.super->destroy(&self->super.super);
}

const struct ums_class_t UMS_CLASS_GENERATOR = {
        .super = &UMS_CLASS_DEVICE,
        .object_size = sizeof(ums_generator_o),
        .class_name = "UmsGenerator",
        .init = (ums_class_init_f) init,
        .destroy = (ums_class_destroy_f) destroy
};

void
ums_generator_init(
        void)
{
        ums_builder_add(&builder);
}
