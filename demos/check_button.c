/**
 * File:   check_button.c
 * Author: AWTK Develop Team
 * Brief:  check_button demo
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

static ret_t on_changed(void* ctx, event_t* e) {
  check_button_t* btn = CHECK_BUTTON(e->target);
  widget_t* widget = WIDGET(e->target);

  log_debug("%s on_changed: %s\n", widget->name, btn->value ? "true" : "false");

  return RET_OK;
}

widget_t* create_check_button(widget_t* win, bool_t radio, const char* text, int x, int y, int w,
                              int h) {
  widget_t* btn = NULL;

  if (radio) {
    btn = check_button_create_radio(win, x, y, w, h);
  } else {
    btn = check_button_create(win, x, y, w, h);
  }

  widget_on(btn, EVT_VALUE_CHANGED, on_changed, NULL);

  widget_set_name(btn, text);
  widget_set_text_utf8(btn, text);

  return btn;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  create_check_button(win, FALSE, "Zzzzzz", 10, 10, 128, 30);
  create_check_button(win, FALSE, "Lzzzzz", 10, 50, 128, 30);
  create_check_button(win, FALSE, "Gzzzzz", 10, 90, 128, 30);

  create_check_button(win, TRUE, "Aaaaaa", 10, 10 + 128, 128, 30);
  create_check_button(win, TRUE, "Waaaaa", 10, 50 + 128, 128, 30);
  create_check_button(win, TRUE, "Tttttt", 10, 90 + 128, 128, 30);
  create_check_button(win, TRUE, "Kkkkkk", 10, 130 + 128, 128, 30);

  widget_layout(win);
  
  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
