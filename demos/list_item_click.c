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

static ret_t on_click(void* ctx, event_t* e) {
  widget_t* item = WIDGET(ctx);
  log_debug("%s clicked\n", item->name);

  return RET_OK;
}

ret_t application_init() {
  uint32_t i = 0;
  uint32_t n = 100;
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* list_view = list_view_create(win, 0, 0, win->w, win->h);
  widget_t* scroll_view = scroll_view_create(list_view, 0, 0, win->w-10, win->h);
  widget_t* scroll_bar = scroll_bar_create_mobile(list_view, win->w-10, 0, 10, win->h);
  
  list_view_set_item_height(list_view, 30);
  for(i = 0; i < n; i++) {
    char text[32] = {0};
    widget_t* item = list_item_create(scroll_view, 0, 0, 0, 0);

    tk_snprintf(text, sizeof(text), "%d", i);
    widget_set_text_utf8(item, text);
    widget_set_name(item, text);
    widget_on(item, EVT_CLICK, on_click, item);
  }

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
