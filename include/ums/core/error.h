/**
 * @file
 * @brief
 * @details
 *
 * @date создан 21.05.2019
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

#ifndef UMS_CORE_ERROR_H_
#define UMS_CORE_ERROR_H_

#include "logger.h"

#ifdef __cplusplus
extern "C" {
#endif

extern struct ums_logger_o *
ums_error_get_logger(
        void);

extern void
ums_error_set(
        const char *error);

extern void
ums_report(
        const int level,
        const char *file,
        const int line,
        const char *msg,
        ...);

#define _FATAL(err) ums_report(LOG_FATAL, __FILE__, __LINE__, err)
#define _ERROR(err) ums_report(LOG_ERROR, __FILE__, __LINE__, err)
#define _WARNING(err) ums_report(LOG_WARNING, __FILE__, __LINE__, err)

extern const char *
ums_error_get(
        void);

#ifdef __cplusplus
}
#endif

#endif /* UMS_CORE_ERROR_H_ */
