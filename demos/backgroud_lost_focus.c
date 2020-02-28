/**
 * File:   edit.c
 * Author: AWTK Develop Team
 * Brief:  edit demo
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

static ret_t on_close(void* ctx, event_t* e) {
  widget_t* win = widget_get_window(WIDGET(e->target));

  window_close(win);

  return RET_OK;
}

static ret_t on_timer_open(const timer_info_t* info) {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* button = button_create(win, 0, 0, 0, 0);

  widget_set_name(win, "next");
  widget_set_text(button, L"Close");
  widget_set_self_layout_params(button, "c", "b:60", "60%", "30");
  widget_on(button, EVT_CLICK, on_close, NULL);

  widget_layout(win);

  return RET_REMOVE;
}

ret_t application_init(void) {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* edit = edit_create(win, 0, 0, win->w, 30);

  widget_set_name(win, "main");
  timer_add(on_timer_open, NULL, 6000);

  widget_layout(win);
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
