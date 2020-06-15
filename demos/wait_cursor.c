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

static ret_t on_wait_done(const timer_info_t* info) {
  widget_t* button = WIDGET(info->ctx);
  widget_end_wait_pointer_cursor(button);

  return RET_REMOVE;
}

static ret_t click_to_wait(void* ctx, event_t* e) {
  widget_t* button = WIDGET(e->target);
  widget_begin_wait_pointer_cursor(button, TRUE);

  timer_add(on_wait_done, button, 3000);

  return RET_OK;
}

static ret_t click_to_quit(void* ctx, event_t* e) {
  tk_quit();

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* button = button_create(win, 0, 0, 0, 0);

  locale_info_change(locale_info(), "zh", "CN");

  widget_set_tr_text(button, "Button");
  widget_set_self_layout_params(button, "center", "middle", "50%", "30");
  widget_on(button, EVT_CLICK, click_to_wait, NULL);
  
  button = button_create(win, 0, 0, 0, 0);
  widget_set_tr_text(button, "Quit");
  widget_set_self_layout_params(button, "center", "middle:50", "50%", "30");
  widget_set_prop_str(button, WIDGET_PROP_POINTER_CURSOR, "cursor_hand");
  widget_on(button, EVT_CLICK, click_to_quit, NULL);

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
