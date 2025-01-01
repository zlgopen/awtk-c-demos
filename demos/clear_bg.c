/**
 * File:   context_menu.c
 * Author: AWTK Develop Team
 * Brief:  context demo
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

static ret_t on_context_menu(void* ctx, event_t* e) {
  pointer_event_t* evt = pointer_event_cast(e);
  widget_t* menu = popup_create(NULL, evt->x, evt->y, 128, 100);
  widget_t* b1 = button_create(menu, 2, 2, 124, 30);
  widget_t* b2 = button_create(menu, 2, 34, 124, 30);
  widget_t* b3 = button_create(menu, 2, 66, 124, 30);

  widget_set_text_utf8(b1, "Copy");
  widget_set_text_utf8(b2, "Paste");
  widget_set_text_utf8(b3, "Cut");

  popup_set_close_when_click(menu, TRUE);

  return RET_OK;
}


ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* label = label_create(win, 0, 10, 200, 80);

  widget_set_text_utf8(label, "right click this window \nto show context menu.");

  widget_on(win, EVT_CONTEXT_MENU, on_context_menu, win);

  widget_set_style_color(win, STYLE_ID_BG_COLOR, 0x00);
  widget_set_style_int(win, STYLE_ID_CLEAR_BG, 1);

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
