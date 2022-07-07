/**
 * File:   chinese.c
 * Author: AWTK Develop Team
 * Brief:  chinese demo
 *
 * Copyright (c) 2018 - 2021  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
 * 2022-07-07 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_click(void* ctx, event_t* e) {
  tk_quit();
  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* quit = button_create(win, 0, 0, 0, 0);
  widget_t* label = label_create(win, 0, 0, 0, 0);

  widget_set_text_utf8(label, "中文演示");
  
  widget_set_name(quit, "quit");
  widget_set_text(quit, L"关闭");
  widget_set_self_layout_params(label, "center", "middle", "50%", "30");
  widget_set_self_layout_params(quit, "center", "bottom:50", "50%", "30");

  widget_on(quit, EVT_CLICK, on_click, NULL);

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
