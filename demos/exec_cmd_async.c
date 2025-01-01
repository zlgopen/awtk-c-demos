/**
 * File:   exec_cmd_async.c
 * Author: AWTK Develop Team
 * Brief:  exec cmd async
 *
 * Copyright (c) 2020 - 2025  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
#include "exec_cmd_async.h"

typedef struct _exec_cmd_info_t {
  str_t cmd;
  void* ctx;
  exec_cmd_on_result_t on_result;
} exec_cmd_info_t;

static exec_cmd_info_t* exec_cmd_info_create(exec_cmd_on_result_t on_result, void* ctx) {
  exec_cmd_info_t* info = NULL;

  info = TKMEM_ZALLOC(exec_cmd_info_t);
  return_value_if_fail(info != NULL, NULL);

  info->ctx = ctx;
  str_init(&(info->cmd), 0);
  info->on_result = on_result;

  return info;
}

static ret_t exec_cmd_info_destroy(exec_cmd_info_t* info) {
  return_value_if_fail(info != NULL, RET_BAD_PARAMS);
  str_reset(&(info->cmd));
  TKMEM_FREE(info);

  return RET_OK;
}

static ret_t async_exec_cmd(void* ctx) {
  exec_cmd_info_t* info = (exec_cmd_info_t*)ctx;

  int result = system(info->cmd.str);
  if(info->on_result != NULL) {
    info->on_result(info->ctx, result);
  }

  log_debug("cmd:%s result=%d\n", info->cmd.str, result);

  return RET_OK;
}

static ret_t async_on_result_cmd(void* ctx, ret_t result) {
  exec_cmd_info_t* info = (exec_cmd_info_t*)ctx;
  exec_cmd_info_destroy(info);

  return RET_OK;
}

ret_t exec_cmd_async(const wchar_t* cmd, exec_cmd_on_result_t on_result, void* ctx) {
  exec_cmd_info_t* info = NULL;
  return_value_if_fail(cmd != NULL, RET_BAD_PARAMS);

  info = exec_cmd_info_create(on_result, ctx);
  return_value_if_fail(info != NULL, RET_OOM);
  str_from_wstr(&(info->cmd), cmd);

  return async_call(async_exec_cmd, async_on_result_cmd, info);
}

ret_t exec_cmd_async_utf8(const char* cmd, exec_cmd_on_result_t on_result, void* ctx) {
  exec_cmd_info_t* info = NULL;
  return_value_if_fail(cmd != NULL, RET_BAD_PARAMS);

  info = exec_cmd_info_create(on_result, ctx);
  return_value_if_fail(info != NULL, RET_OOM);
  str_set(&(info->cmd), cmd);

  return async_call(async_exec_cmd, async_on_result_cmd, info);
}

