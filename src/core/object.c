/**
 * @file
 * @brief
 * @details
 *
 * @date создан  4.05.2019
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
#include <stdlib.h>
#include <string.h>

#define _UMS_PROTECTED_
#include <ums/core/object.h>
#undef _UMS_PROTECTED_
#include <ums/core/error.h>

/*
 * @brief Создание и начальная инициализация объекта.
 * @details
 * @param bar Указатель на заготовку объекта или NULL, если объект нужно создать в куче.
 * @param oclass Указатель на класс.
 * @param init_data Указатель на данные инициализации.
 * @return
 */
void *
ums_object_create(
        void *bar,
        const ums_class_t *oclass,
        const void *init_data)
{
        if (oclass == NULL) {
                _FATAL("In ums_object_create(*bar, *oclass) #oclass is NULL.\n");
                return NULL;
        }

        int flags = 0;
        ums_object_o *result = bar;

        if (result != NULL) {
                flags = UMS_OBJECT_FLAG_STATIC;
        } else {
                result = malloc(oclass->object_size);
        }

        result->lock = 1;
        result->flags = flags;
        result->klass = oclass;
        result->klass->init(result, init_data);
        return result;
}

/*
 * @brief Приведение к типу класса.
 * @details Проверяет, принадлежит ли obj классу oclass или производному классу.
 * @param obj Указатель на объект.
 * @param oclass Указатель на класс.
 * @return Если obj принадлежит классу oclass или его потомку, то возвращается obj, иначе
 *      возвращается NULL. Так же возвращается NULL если obj равен NULL.
 */
void *
ums_object_cast(
        const void *obj,
        const ums_class_t *oclass)
{
        if (obj == NULL) {
                _FATAL("In ums_object_cast(*obj, *oclass) #obj is NULL.\n");
                return NULL;
        }

        if (oclass == NULL) {
                _FATAL("In ums_object_cast(*obj, *oclass) #oclass is NULL.\n");
                return NULL;
        }

        const ums_object_o *o = obj;
        const ums_class_t *cl = o->klass;

        for (int i = 0; i < UMS_CLASS_MAX_NESTING; i++) {
                if (cl == NULL) {
                        break;
                }

                if (cl == oclass) {
                        return (void *) obj;
                }

                cl = cl->super;
        }

        return NULL;
}

extern int
ums_object_compare(
        const void *left,
        const void *right)
{
        if (left == NULL) {
                _FATAL("In ums_object_is_equal(*left, *right) #left is NULL.\n");
                return 0;
        }

        ums_object_o *l = ums_object_cast(left, &UMS_CLASS_OBJECT);

        if (l == NULL) {
                _FATAL("In ums_object_is_equal(*left, *right) #left is not object.\n");
                return 0;
        }

        if (right == NULL) {
                _FATAL("In ums_object_is_equal(*left, *right) #right is NULL.\n");
                return 0;
        }

        ums_object_o *r = ums_object_cast(right, &UMS_CLASS_OBJECT);

        if (r == NULL) {
                _FATAL("In ums_object_is_equal(*left, *right) #right is not object.\n");
                return 0;
        }

        return l->klass->compare == NULL ? l - r : l->klass->compare(l, r);
}

extern void *
ums_object_copy(
        const void *obj)
{
        if (obj == NULL) {
                _FATAL("In ums_object_copy(*obj) #obj is NULL.\n");
                return NULL;
        }

        ums_object_o *o = ums_object_cast(obj, &UMS_CLASS_OBJECT);

        if (o == NULL) {
                _FATAL("In ums_object_copy(*obj) #obj is not object.\n");
                return NULL;
        }

        return o->klass->copy == NULL ? NULL : o->klass->copy(o);
}

/*
 *
 * @param obj
 */
void
ums_object_lock(
        void *obj)
{
        if (obj == NULL) {
                _FATAL("In ums_object_lock(*obj) #obj is NULL.\n");
                return;
        }

        ums_object_o *o = ums_object_cast(obj, &UMS_CLASS_OBJECT);

        if (o == NULL) {
                _ERROR("In ums_object_lock(*obj) #obj is not object.\n");
                return;
        }

        o->lock++;
}

/*
 *
 * @param obj
 */
void
ums_object_unlock(
        void *obj)
{
        if (obj == NULL) {
                _FATAL("In ums_object_unlock(*obj) #obj is NULL.\n");
                return;
        }

        ums_object_o *o = ums_object_cast(obj, &UMS_CLASS_OBJECT);

        if (o == NULL) {
                _ERROR("In ums_object_unlock(*obj) #obj is not object.\n");
                return;
        }

        o->lock--;

        if (o->lock != 0) {
                return;
        }

        o->klass->destroy(o);
        int flag = o->flags & UMS_OBJECT_FLAG_STATIC;
        memset(o, 0, o->klass->object_size);

        if (flag == 0) {
                free(o);
        }
}

/*
 * Возвращает имя класса объекта.
 * @param obj Указатель на объект.
 * @return Возвращает имя класса или NULL если obj не является указателем на объект.
 */
const char *
ums_object_class_name(
        void *obj)
{
        if (obj == NULL) {
                _FATAL("In ums_object_get_class_name(*obj) #obj is NULL.\n");
                return NULL;
        }

        ums_object_o *o = ums_object_cast(obj, &UMS_CLASS_OBJECT);

        if (o == NULL) {
                _ERROR("In ums_object_get_class_name(*obj) #obj is not object.\n");
                return NULL;
        }

        return o->klass->class_name;
}

/*
 * Показывает, является ли объект статическим или же он размещён в куче.
 * @param obj Указатель на объект.
 * @return Если объект размещён в куче, то возвращает ноль. Для статического объекта
 *      возвращается ненулевое значение.
 */
int
ums_object_is_static(
        void *obj)
{
        if (obj == NULL) {
                _FATAL("In ums_object_is_static(*obj) #obj is NULL.\n");
                return 0;
        }

        ums_object_o *o = ums_object_cast(obj, &UMS_CLASS_OBJECT);

        if (o == NULL) {
                _ERROR("In ums_object_is_static(*obj) #obj is not object.\n");
                return 0;
        }

        return o->flags & UMS_OBJECT_FLAG_STATIC;
}

/******************************************************************************
 * Statistics
 *****************************************************************************/
typedef struct {
        const ums_class_t *_class;
        size_t _mem_used;
        size_t _mem_max;
        size_t _static_used;
        size_t _static_max;
} alloc_info_t;

static int stat_size;
static alloc_info_t stat[256];

static alloc_info_t *
info_find(
        const ums_class_t *_class)
{
        for (int i = 0; i < stat_size; i++) {
                alloc_info_t *result = &stat[i];

                if (result->_class == _class) {
                        return result;
                }
        }

        return NULL;
}

static alloc_info_t *
info_add(
        const ums_class_t *_class)
{
        if (stat_size >= 256 - 1) {
                return NULL;
        }

        alloc_info_t *info = &stat[stat_size++];
        info->_class = _class;
        info->_mem_used = 0;
        info->_mem_max = 0;
        info->_static_used = 0;
        info->_static_max = 0;
        return info;
}

static void
info_plus(
        ums_object_o *obj)
{
        alloc_info_t *info = info_find(obj->klass);

        if (info == NULL) {
                info = info_add(obj->klass);
        }

        if (info == NULL) {
                return;
        }

        if ((obj->flags & UMS_OBJECT_FLAG_STATIC) == 0) {
                info->_mem_used++;

                if (info->_mem_max < info->_mem_used) {
                        info->_mem_max = info->_mem_used;
                }
        } else {
                info->_static_used++;

                if (info->_static_max < info->_static_used) {
                        info->_static_max = info->_static_used;
                }
        }
}

static void
info_minus(
        ums_object_o *obj)
{
        alloc_info_t *info = info_find(obj->klass);

        if (info == NULL) {
                return;
        }

        if ((obj->flags & UMS_OBJECT_FLAG_STATIC) == 0) {
                info->_mem_used--;
        } else {
                info->_static_used--;
        }
}

void
ums_object_print_used(
        void)
{
        size_t max = 0, alloc = 0;
        const char *s9 = "---------";
        const char *s23 = "-----------------------";
        printf("\nStatistics of objects.\n");
        printf("+%-23s+%-9s+%-9s+%-9s+%-9s+%-9s+\n", s23, s9, s9, s9, s9, s9);
        printf("|%-23s|%-9s|%-9s|%-9s|%-9s|%-9s|\n", " class name", " size of", " used",
               " used", " maximum", " maximum");
        printf("|%-23s|%-9s|%-9s|%-9s|%-9s|%-9s|\n", "", " object", " dynamic", " static",
               " dynamic", " static");
        printf("+%-23s+%-9s+%-9s+%-9s+%-9s+%-9s+\n", s23, s9, s9, s9, s9, s9);

        for (int i = 0; i < stat_size; i++) {
                alloc_info_t *info = &stat[i];
                printf("| %-22s|%9u|%9zu|%9zu|%9zu|%9zu|\n", info->_class->class_name,
                       info->_class->object_size, info->_mem_used, info->_static_used,
                       info->_mem_max, info->_static_max);
                max += info->_mem_max * info->_class->object_size;
                alloc += info->_mem_used * info->_class->object_size;
                printf("+%-23s+%-9s+%-9s+%-9s+%-9s+%-9s+\n", s23, s9, s9, s9, s9, s9);
        }

        printf("alloc/max %zu/%zu\n\n", alloc, max);
}

/******************************************************************************
 * Inside class
 *****************************************************************************/

static void
init(
        ums_object_o *obj,
        const void *init_data)
{
        info_plus(obj);
}

static void
destroy(
        ums_object_o *obj)
{
        info_minus(obj);
}

static ums_object_o *
copy(
        const ums_object_o *obj)
{
        return ums_object_create(NULL, obj->klass, 0);
}

static int
compare(
        const ums_object_o *obj,
        const ums_object_o *cmp)
{
        return obj - cmp;
}

const ums_class_t UMS_CLASS_OBJECT = {
        .super = 0,
        .object_size = sizeof(ums_object_o),
        .class_name = "UmsObject",
        .init = init,
        .destroy = destroy,
        .copy = copy,
        .compare = compare
};
