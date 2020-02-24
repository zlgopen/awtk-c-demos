/**
 * File:   basic.c
 * Author: AWTK Develop Team
 * Brief:  demo for open window and install event handlers
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
 * 2018-08-18 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_inc(void* ctx, event_t* e) {
  widget_t* win = WIDGET(ctx);
  widget_t* bar1 = widget_child(win, "bar1");
  widget_t* bar2 = widget_child(win, "bar2");

  widget_add_value(bar1, 10);
  widget_add_value(bar2, 10);

  return RET_OK;
}

static ret_t on_dec(void* ctx, event_t* e) {
  widget_t* win = WIDGET(ctx);
  widget_t* bar1 = widget_child(win, "bar1");
  widget_t* bar2 = widget_child(win, "bar2");

  widget_add_value(bar1, -10);
  widget_add_value(bar2, -10);

  return RET_OK;
}

static ret_t on_close(void* ctx, event_t* e) {
  widget_t* win = WIDGET(ctx);
  widget_t* bar1 = widget_child(win, "bar1");
  widget_t* bar2 = widget_child(win, "bar2");

  log_debug("bar1->value=%d\n", (int)(widget_get_value(bar1)));
  log_debug("bar2->value=%d\n", (int)(widget_get_value(bar2)));

  tk_quit();

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_open("basic");

  widget_child_on(win, "inc_value", EVT_CLICK, on_inc, win);
  widget_child_on(win, "dec_value", EVT_CLICK, on_dec, win);
  widget_child_on(win, "close", EVT_CLICK, on_close, win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"

