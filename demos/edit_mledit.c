/**
 * File:   edit_mledit.c
 * Author: AWTK Develop Team
 * Brief:  edit demo
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
 * 2018-08-16 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_click_close(void* ctx, event_t* e) {
  widget_t* mledit = WIDGET(ctx);

  tk_quit();

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  widget_t* edit = edit_create(win, 0, 0, 0, 0);
  widget_t* mledit = mledit_create(win, 0, 0, 0, 0);
  widget_t* close = button_create(win, 0, 0, 0, 0);

  widget_set_text(close, L"close");
  widget_set_self_layout_params(close, "center", "bottom:10", "50%", "30");
  widget_on(close, EVT_CLICK, on_click_close, NULL);

  edit_set_input_tips(edit, "title");
  mledit_set_input_tips(mledit, "content");
  widget_set_self_layout_params(edit, "10", "10", "80%", "30");
  widget_set_self_layout_params(mledit, "10", "50", "80%", "60%");

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
