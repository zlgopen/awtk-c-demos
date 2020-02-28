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

static ret_t on_click(void* ctx, event_t* e) {
  widget_t* mledit = WIDGET(ctx);

  widget_set_text(mledit, L"中文　    a b c 123\nnext line");

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  widget_t* mledit = mledit_create(win, 0, 0, win->w, win->h / 2);
  widget_t* button = button_create(win, 0, 0, 0, 0);

  widget_set_text(mledit, L"multi line edit");

  widget_set_text(button, L"SetText");
  widget_set_self_layout_params(button, "c", "b:60", "40%", "30");
  widget_on(button, EVT_CLICK, on_click, mledit);

  widget_set_name(mledit, "mledit");
  widget_on(mledit, EVT_VALUE_CHANGED, on_change, NULL);
  widget_on(mledit, EVT_VALUE_CHANGING, on_change, NULL);

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
