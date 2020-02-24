/**
 * File:   text_selector.c
 * Author: AWTK Develop Team
 * Brief:  text_selector demo
 *
 * Copyright (c) 2019 - 2020  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
 * 2019-01-15 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_changed(void* ctx, event_t* e) {
  log_debug("on_changed\n");
  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  widget_t* ts = text_selector_create(win, 10, 10, 80, 150);
  text_selector_set_options(ts, "1:red;2:green;3:blue;4:orange;5:gold");
  text_selector_set_value(ts, 1);
  widget_use_style(ts, "dark");

  widget_on(ts, EVT_VALUE_CHANGED, on_changed, NULL);
  
  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
