/**
 * File:   5keys.c
 * Author: AWTK Develop Team
 * Brief:  用于支持只有方向键和OK键的情况。
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
 * 2021-06-15 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_inc(void* ctx, event_t* e) {
  widget_t* value = widget_lookup(WIDGET(ctx), "value", TRUE);

  widget_add_value(value, 1);

  return RET_OK;
}

static ret_t on_dec(void* ctx, event_t* e) {
  widget_t* value = widget_lookup(WIDGET(ctx), "value", TRUE);

  widget_add_value(value, -1);

  return RET_OK;
}

static ret_t on_reset(void* ctx, event_t* e) {
  widget_t* value = widget_lookup(WIDGET(ctx), "value", TRUE);
  widget_set_value(value, 0);

  return RET_OK;
}

ret_t application_init() {
  system_info_set_keyboard_type(system_info(), KEYBOARD_5KEYS);

  widget_t* win = window_open("5keys");

  widget_child_on(win, "inc", EVT_CLICK, on_inc, win);
  widget_child_on(win, "dec", EVT_CLICK, on_dec, win);
  widget_child_on(win, "reset", EVT_CLICK, on_reset, win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
