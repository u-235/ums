/**
 * @file
 * @brief
 * @details
 *
 * @date создан 20.04.2019
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

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ums/core.h>

static struct ums_logger_o *log;
static struct ums_device_o *sim;

void
print_dev(struct ums_device_o *dev)
{
        static int lvl = 0;
        char str[256];

        if (dev == NULL) {
                return;
        }

        *str = 0;

        for (int i = 0; i < lvl; i++) {
                strcat(str, "|   ");
        }

        printf("%s|\n", str);
        printf("%s+-> %s\n", str, ums_device_get_name(dev));
        printf("%s|   class  %s\n", str, ums_object_class_name(dev));
        printf("%s|   id     %i\n", str, ums_device_get_id(dev));
        printf("%s|   passed %lli.%lli\n", str,
               (long long) ums_device_get_passed(dev) / 1000000000,
               ums_device_get_passed(dev) % 1000000000);
        printf("%s|   cycle  %lli\n", str, ums_device_get_cycle(dev));

        lvl++;
        struct ums_list_o *child_list = ums_device_get_childs(dev);
        int max = ums_list_lenght(child_list);

        for (int i = 0; i < max; i++) {
                struct ums_device_o *child = ums_list_item(child_list, i);
                print_dev(child);
        }

        lvl--;

        if (lvl == 0) {
                printf("\n");
        }
}

int
main(void)
{
        clock_t cl;

        ums_core_init(LOG_DEBUG);
        log = ums_error_get_logger();
        ums_logger_print(log, LOG_DEBUG, "start\n\n");
        sim = ums_simulator_get();

        struct ums_device_o *dev;
        dev = ums_build("_test_1");
        ums_device_add(sim, dev);
        ums_object_unlock(dev);

        dev = ums_build("_test_2");
        ums_device_add(sim, dev);
        ums_object_unlock(dev);

        struct ums_device_o *dev2;
        dev2 = ums_build("_test_3");
        ums_device_add(dev, dev2);
        ums_device_remove(dev, dev2);
        ums_object_unlock(dev2);

        dev = ums_build("generator");
        struct ums_value_o *val = ums_value_make(NULL);
        ums_value_set_dword(val, 13000007);
        ums_device_set_property(dev, "frequency", val);
        ums_device_add(sim, dev);
        ums_object_unlock(dev);

        dev = ums_build("generator");
        ums_value_set_qword(val, 250000);
        ums_device_set_property(dev, "period", val);
        ums_device_add(sim, dev);
        ums_object_unlock(dev);

        ums_object_unlock(val);

        ums_simulator_reset();
        cl = clock();
        ums_simulator_run(1000000000);
        cl = clock() - cl;
        float sec = ((float) cl) / CLOCKS_PER_SEC;
        float freq = ((float) ums_device_get_cycle(sim)) / sec / 1000000;
        fflush(stderr);
        fflush(stdout);
        print_dev(sim);
        printf("time %f sec\n", sec);
        printf("freq %f Mcycle/sec\n", freq);
        ums_object_unlock(sim);
        ums_object_print_used();
        return 0;
}
