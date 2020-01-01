/**
 * File:   mledit.c
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

static ret_t on_change(void* ctx, event_t* evt) {
  widget_t* target = WIDGET(evt->target);

  if (evt->type == EVT_VALUE_CHANGING) {
    log_debug("%s changing\n", target->name);
  } else {
    log_debug("%s changed\n", target->name);
  }

  return RET_OK;
}

static ret_t on_set_text(void* ctx, event_t* e) {
  char str[32];
  widget_t* mledit = WIDGET(ctx);
  widget_t* win = widget_get_window(WIDGET(e->target));

  tk_snprintf(str, sizeof(str), "rand:%d", random());
  widget_set_text_utf8(mledit, str);

  return RET_OK;
}

static ret_t on_close(void* ctx, event_t* e) {
  widget_t* win = widget_get_window(WIDGET(e->target));

  window_close(win);

  return RET_OK;
}

static ret_t on_open_window(void* ctx, event_t* e) {
  widget_t* mledit = WIDGET(ctx);

  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* button = button_create(win, 0, 0, 0, 0);

  widget_set_text(button, L"Set Random Text");
  widget_set_self_layout_params(button, "c", "b:160", "60%", "30");
  widget_on(button, EVT_CLICK, on_set_text, mledit);

  button = button_create(win, 0, 0, 0, 0);

  widget_set_text(button, L"Close");
  widget_set_self_layout_params(button, "c", "b:60", "60%", "30");
  widget_on(button, EVT_CLICK, on_close, NULL);

  widget_layout(win);

  return RET_OK;
}

void application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  widget_t* mledit = mledit_create(win, 0, 0, win->w, win->h / 2);
  widget_t* button = button_create(win, 0, 0, 0, 0);

  widget_set_text(button, L"OpenWindow");
  widget_set_self_layout_params(button, "c", "b:60", "40%", "30");
  widget_on(button, EVT_CLICK, on_open_window, mledit);

  widget_set_name(mledit, "mledit");
  widget_set_text(mledit, L"multi line edit");
  widget_on(mledit, EVT_VALUE_CHANGED, on_change, NULL);
  widget_on(mledit, EVT_VALUE_CHANGING, on_change, NULL);

  widget_layout(win);
}

#include "demo_main.c"
