/**
 * File:   button.c
 * Author: AWTK Develop Team
 * Brief:  button demo
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

static ret_t on_open_button(void* ctx, event_t* e);

static ret_t win_after_open(widget_t* win, const char* text, event_func_t func) {
  widget_t* close = widget_lookup(win, "close", TRUE);

  widget_set_text_utf8(close, text);
  widget_child_on(win, "close", EVT_CLICK, func, NULL);
  widget_layout(win);

  return RET_OK;
}

static ret_t on_open_basic(void* ctx, event_t* e) {
  widget_t* win = window_open_and_close("basic", widget_get_window(WIDGET(e->target)));
  widget_t* close = widget_lookup(win, "close", TRUE);

  widget_set_text_utf8(close, "Open Button");
  widget_on(close, EVT_CLICK, on_open_button, NULL);
  widget_layout(win);

  return RET_OK;
}

static ret_t on_open_button(void* ctx, event_t* e) {
  widget_t* win = window_open_and_close("button", widget_get_window(WIDGET(e->target)));
  widget_t* close = widget_lookup(win, "close", TRUE);

  widget_set_text_utf8(close, "Open Basic");
  widget_on(close, EVT_CLICK, on_open_basic, NULL);
  widget_layout(win);

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_open("basic");
  widget_t* close = widget_lookup(win, "close", TRUE);

  widget_set_text_utf8(close, "Open Button");
  widget_on(close, EVT_CLICK, on_open_button, NULL);
  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
