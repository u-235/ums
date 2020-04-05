/**
 * @file
 * @brief
 * @details
 *
 * @date создан 30.05.2019
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
 *
 */

#ifndef UMS_CORE_OBJECT_H_
#define UMS_CORE_OBJECT_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct ums_class_t;

struct ums_object_o;
extern const struct ums_class_t UMS_CLASS_OBJECT;

/**
 *
 * @param bar
 * @param oclass
 * @param init_data
 * @return
 */
extern void *
ums_object_create(
        void *bar,
        const struct ums_class_t *oclass,
        const void *init_data);

/**
 * @brief Casts object to class.
 * @details Checks whether @b obj belongs to the class @b oclass or derived class.
 * @param obj Pointer to object.
 * @param oclass Pointer to class.
 * @return If obj belongs to the class @b oclass or its descendant, then @b obj is returned,
 *      otherwise NULL is returned. It also returns NULL if @b obj is NULL.
 */
extern void *
ums_object_cast(
        const void *obj,
        const struct ums_class_t *oclass);

/**
 *
 * @param left
 * @param right
 * @return
 */
extern int
ums_object_compare(
        const void *left,
        const void *right);

/**
 *
 * @param obj
 */
extern void *
ums_object_copy(
        const void *obj);

/**
 *
 * @param obj
 */
extern void
ums_object_lock(
        void *obj);

/**
 *
 * @param obj
 */
extern void
ums_object_unlock(
        void *obj);

/**
 *
 * @param obj
 * @return
 */
extern const char *
ums_object_class_name(
        void *obj);

/**
 *
 * @param obj
 * @return
 */
extern int
ums_object_is_static(
        void *obj);

extern void
ums_object_print_used(
        void);

/*******************************************************************************
 * sections : protected
 ******************************************************************************/

#ifdef _UMS_PROTECTED_

#define UMS_CLASS_MAX_NESTING 42

/**
 *
 * @param self
 * @param init_data
 */
typedef void (*ums_class_init_f)(
        struct ums_object_o *self,
        const void *init_data);

/**
 *
 * @param self
 */
typedef void (*ums_class_destroy_f)(
        struct ums_object_o *self);

/**
 *
 * @param self
 * @param obj
 * @return
 */
typedef int (*ums_class_compare_f)(
        const struct ums_object_o *self,
        const struct ums_object_o *obj);

/**
 *
 * @param self
 * @return
 */
typedef struct ums_object_o *(*ums_class_copy_f)(
        const struct ums_object_o *self);

/**
 *
 */
typedef struct ums_class_t {
        const struct ums_class_t *super;

        const size_t object_size;
        const char *class_name;

        const ums_class_init_f init;
        const ums_class_destroy_f destroy;
        const ums_class_compare_f compare;
        const ums_class_copy_f copy;
} ums_class_t;

/** Flag to mark static object. */
#define UMS_OBJECT_FLAG_STATIC  0x0001

typedef struct ums_object_o {
        const ums_class_t *klass;

        int flags;
        int lock;
} ums_object_o;

#endif /* _UMS_PROTECTED_ */

#ifdef __cplusplus
}
#endif

#endif /* UMS_CORE_OBJECT_H_ */
