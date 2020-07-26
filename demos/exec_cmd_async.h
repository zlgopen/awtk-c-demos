/**
 * File:   exec_cmd_async.h
 * Author: AWTK Develop Team
 * Brief:  exec cmd async
 *
 * Copyright (c) 2020 - 2020  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2020-07-26 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"
#include "tkc/async.h"

#ifndef TK_EXEC_CMD_ASYNC_H
#define TK_EXEC_CMD_ASYNC_H

BEGIN_C_DECLS

typedef ret_t (*exec_cmd_on_result_t)(void* ctx, int result);

/**
 * @class exec_cmd_async_t
 * @annotation ["fake"]
 * 异步执行一个外部命令。
 */

/**
 * @method exec_cmd_async
 * @annotation ["static"]
 *
 * 异步执行一个外部命令。
 *
 * @param {const wchar_t*} cmd 要执行的命令。
 * @param {exec_cmd_on_result_t} on_result 执行完成后的回调函数(可以为空)。
 * @param {void*} ctx 回调函数的上下文。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败
 */
ret_t exec_cmd_async(const wchar_t* cmd, exec_cmd_on_result_t on_result, void* ctx);

/**
 * @method exec_cmd_async_utf8
 * @annotation ["static"]
 *
 * 异步执行一个外部命令。
 *
 * @param {const char*} cmd 要执行的命令。
 * @param {exec_cmd_on_result_t} on_result 执行完成后的回调函数(可以为空)。
 * @param {void*} ctx 回调函数的上下文。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败
 */
ret_t exec_cmd_async_utf8(const char* cmd, exec_cmd_on_result_t on_result, void* ctx);

END_C_DECLS

#endif /*TK_EXEC_CMD_ASYNC_H*/
