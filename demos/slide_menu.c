/**
 * File:   slide_menu.c
 * Author: AWTK Develop Team
 * Brief:  gif image demo
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

static ret_t on_button_click(void* ctx, event_t* e) {
  log_debug("button_clicked: %s\n", WIDGET(e->target)->name);
  return RET_OK;
}

static ret_t on_current_changed(void* ctx, event_t* e) {
  log_debug("current = %d\n", widget_get_value(WIDGET(e->target)));

  return RET_OK;
}

static void add_button(widget_t* slide_menu, const char* text) {
  widget_t* b = button_create(slide_menu, 0, 0, 0, 0);
  widget_set_name(b, text);
  widget_set_text_utf8(b, text);
  widget_on(b, EVT_CLICK, on_button_click, b);
}

ret_t application_init() {
  widget_t* slide_menu = NULL;
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  slide_menu = slide_menu_create(win, 10, 10, 300, 60);
  add_button(slide_menu, "1");
  add_button(slide_menu, "2");
  add_button(slide_menu, "3");
  add_button(slide_menu, "4");

  widget_on(slide_menu, EVT_VALUE_CHANGED, on_current_changed, slide_menu);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
