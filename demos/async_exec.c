/**
 * File:   async_exec.c
 * Author: AWTK Develop Team
 * Brief:  async exec demo
 *
 * Copyright (c) 2018 - 2025  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
#include "exec_cmd_async.h"

static ret_t on_exec_done(void* ctx, int result) {
  log_debug("exec done: result=%d\n", result);

  return RET_OK;
}

static ret_t on_click(void* ctx, event_t* e) {
  widget_t* cmd = WIDGET(ctx);
  return_value_if_fail(cmd->text.size > 0, RET_FAIL);

  exec_cmd_async(cmd->text.str, on_exec_done, NULL);

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* exec = button_create(win, 0, 0, 0, 0);
  widget_t* cmd = edit_create(win, 0, 0, 0, 0);

  widget_set_text_utf8(exec, "Execute");
  edit_set_input_tips(cmd, "Input cmd at here");
  widget_set_self_layout_params(cmd, "center", "middle", "80%", "30");
  widget_set_self_layout_params(exec, "center", "middle:50", "50%", "30");

  widget_on(exec, EVT_CLICK, on_click, cmd);

  widget_layout(win);

  async_call_init_ex(5, 1);

  return RET_OK;
}

ret_t application_exit() {
  async_call_deinit();

  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
