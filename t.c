/**
 * File:   context_menu.c
 * Author: AWTK Develop Team
 * Brief:  context demo
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
 * 2018-08-16 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_destroy_win(void* ctx, event_t* e) {
  widget_invalidate_force(window_manager(), NULL);
  log_debug("on_destroy_win\n");
  return RET_REMOVE;
}

static ret_t on_pointer_move(void* ctx, event_t* e) {
  paint_event_t* evt = paint_event_cast(e);
  color_t bg = color_init(0, 0, 0, 0xff);
  canvas_set_fill_color(evt->c, bg);
  canvas_clear_rect(evt->c, 0, 0, window_manager()->w, window_manager()->h);
  log_debug("clear\n");

  return RET_OK;
}

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
  widget_on(menu, EVT_DESTROY, on_destroy_win, NULL);

  return RET_OK;
}


ret_t application_init() {
//  widget_set_text_utf8(label, "right click this window \nto show context menu.");
  widget_on(window_manager(), EVT_CONTEXT_MENU, on_context_menu, NULL);
  widget_on(window_manager(), EVT_BEFORE_PAINT, on_pointer_move, NULL);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
