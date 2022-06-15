/**
 * File:   double_click.c
 * Author: AWTK Develop Team
 * Brief:  double click demo
 *
 * Copyright (c) 2018 - 2022  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
 * 2022-06-15 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_double_click(void* ctx, event_t* e) {
  widget_t* button = WIDGET(e->target);
  log_debug("on_double_click: %s\n", button->name);
  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* ok = button_create(win, 0, 0, 0, 0);

  widget_set_name(ok, "ok");
  widget_set_tr_text(ok, "double_click");
  widget_set_self_layout_params(ok, "center", "middle", "50%", "30");

  widget_on(ok, EVT_DOUBLE_CLICK, on_double_click, NULL);

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
