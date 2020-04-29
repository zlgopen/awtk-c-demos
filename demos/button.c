/**
 * File:   button.c
 * Author: AWTK Develop Team
 * Brief:  button demo
 *
 * Copyright (c) 2018 - 2020  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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

static ret_t on_click(void* ctx, event_t* e) {
  log_debug("on_click\n");
  return RET_OK;
}

static ret_t on_long_press(void* ctx, event_t* e) {
  log_debug("on_long_press\n");
  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* ok = button_create(win, 0, 0, 0, 0);

  locale_info_change(locale_info(), "zh", "CN");

  widget_set_tr_text(ok, "ok");
  widget_set_self_layout_params(ok, "center", "middle", "50%", "30");
  widget_on(ok, EVT_CLICK, on_click, NULL);
  widget_on(ok, EVT_LONG_PRESS, on_long_press, NULL);

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
