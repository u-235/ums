/**
 * @file
 * @brief
 * @details
 *
 * @date создан 4.05.2019
 * @author Nick Egorrov
 */

#include <stdlib.h>
#include <string.h>

#define _UMS_PROTECTED_
#include <ums/core/simulator.h>
#undef _UMS_PROTECTED_
#include "init.h"

static ums_simulator_o *single;

ums_device_o *
ums_simulator_get(
        void)
{
        return (ums_device_o *) single;
}

static void
reset_impl(
        ums_device_o *self);

static int
reset_handler(
        void *item,
        void *data)
{
        reset_impl(item);
        return 1;
}

void
reset_impl(
        ums_device_o *self)
{
        self->reset_handler(self);
        ums_list_iterate(&self->childs, reset_handler, 0);
}

void
ums_simulator_reset(
        void)
{
        reset_impl(&single->super);
}

int
resize_workers_array(
        int size)
{
        return -1;

}

static int
add_worker_childs(
        void *dev,
        void *sim);

void
add_worker(
        ums_simulator_o *sim,
        ums_device_o *dev)
{
        if (dev == NULL) {
                return;
        }

        if (ums_list_add(&sim->all_devices, dev) < 0) {
                return;
        }

        ums_list_iterate(&dev->childs, add_worker_childs, sim);
        return;
}

int
add_worker_childs(
        void *dev,
        void *sim)
{
        add_worker(sim, dev);
        return 1;
}

static int
remove_worker_childs(
        void *dev,
        void *sim);

void
remove_worker(
        ums_simulator_o *sim,
        ums_device_o *dev)
{
        if (dev == NULL) {
                return;
        }

        if (ums_list_remove(&sim->all_devices, dev) < 0) {
                return;
        }

        ums_list_iterate(&dev->childs, remove_worker_childs, sim);
        return;
}

int
remove_worker_childs(
        void *dev,
        void *sim)
{
        remove_worker(sim, dev);
        return 1;
}

static ums_time_t
step_impl(
        ums_simulator_o *sim,
        ums_device_o **dev_list,
        int length,
        ums_time_t max)
{
        ums_time_t coming = UMS_TIME_MAX;

        int i = length;
        ums_device_o *dev;
        ums_device_o **dl = dev_list;

        while (i-- > 0) {
                dev = *dl++;

                if (dev->coming < coming) {
                        coming = dev->coming;
                }
        }

        if (coming > max) {
                return sim->super.passed;
        }

        i = length;
        dl = dev_list;
        sim->super.passed = coming;

        while (i-- > 0) {
                dev = *dl++;
                dev->passed = coming;

                if (dev->coming != coming || dev->change_perform == 0) {
                        continue;
                }

                sim->balancer.run(dev->change_perform, dev);
        }

        sim->balancer.wait();

        i = length;
        dl = dev_list;
        sim->super.cycle++;

        while (i-- > 0) {
                dev = *dl++;

                if (dev->coming != coming || dev->change_latch == 0) {
                        continue;
                }

                dev->cycle++;
                sim->balancer.run(dev->change_latch, dev);
        }

        sim->balancer.wait();

        i = length;
        dl = dev_list;

        while (i-- > 0) {
                dev = *dl++;

                if (dev->coming != coming || dev->change_notify == 0) {
                        continue;
                }

                sim->balancer.run(dev->change_notify, dev);
        }

        sim->balancer.wait();

        return sim->super.passed;
}

ums_time_t
ums_simulator_step(
        ums_time_t max)
{
        ums_device_o **all_dev = (ums_device_o **) ums_list_get_raw_deta(&single->all_devices);
        int length = ums_list_lenght(&single->all_devices);
        return step_impl(single, all_dev, length, max);
}

ums_time_t
ums_simulator_run(
        ums_time_t max)
{
        ums_time_t left;
        ums_time_t passed = single->super.passed;
        ums_device_o **all_dev = (ums_device_o **) ums_list_get_raw_deta(&single->all_devices);
        int length = ums_list_lenght(&single->all_devices);

        single->super.status = DEVICE_OK;

        do {
                if (single->super.status != DEVICE_OK) {
                        break;
                }

                left = single->super.passed;
                passed = step_impl(single, all_dev, length, max);
        } while (passed != left);

        return passed;
}

ums_time_t
ums_simulator_breack(
        void)
{
        single->super.status = DEVICE_BREAK;
        return single->super.passed;
}

/******************************************************************************
 * Virtual methods
 *****************************************************************************/

static void
irq(
        ums_device_o *self,
        int reason)
{
        self->status = reason;
}

static void
changed_child(
        ums_device_o *self,
        ums_device_o *child)
{
        ums_simulator_o *sim = (void *) self;

        if (child->parent == NULL) {
                remove_worker(sim, child);
        } else {
                add_worker(sim, child);
        }
}

static void
run(
        void (*run_func)(struct ums_device_o *dev),
        struct ums_device_o *dev)
{
        run_func(dev);
        return;
}

static void
wait(void)
{
        return;
}

/******************************************************************************
 * Inside class
 *****************************************************************************/

static void
init(
        ums_simulator_o *self,
        const void *init_data)
{
        UMS_CLASS_SIMULATOR.super->init(&self->super.super, init_data);

        self->super.irq_handler = irq;
        self->super.send_parent_report = changed_child;
        self->balancer.run = run;
        self->balancer.wait = wait;
        ums_list_make(&self->all_devices, &UMS_CLASS_DEVICE);
}

static void
destroy(
        ums_simulator_o *self)
{
        ums_list_remove_all(&self->all_devices);
        ums_object_unlock(&self->all_devices);

        UMS_CLASS_SIMULATOR.super->destroy(&self->super.super);
}

const ums_class_t UMS_CLASS_SIMULATOR = {
        .super = &UMS_CLASS_DEVICE,
        .object_size = sizeof(ums_simulator_o),
        .class_name = "UmsSimulator",
        .init = (ums_class_init_f) init,
        .destroy = (ums_class_destroy_f) destroy
};

void
ums_simulator_init(
        void)
{
        single = ums_object_create(NULL, &UMS_CLASS_SIMULATOR, 0);
        single->super._make(&single->super, "simulator");
}
