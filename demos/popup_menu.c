/**
 * File:   popup_menu.c
 * Author: AWTK Develop Team
 * Brief:  popup menu
 *
 * Copyright (c) 2020 - 2025  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
 * 2020-06-14 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_click(void* ctx, event_t* e) {
  const char* win_name = (const char*)ctx;

  window_open(win_name);

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* ok = button_create(win, 0, 0, 0, 0);
  widget_set_tr_text(ok, "...");
  widget_set_self_layout_params(ok, "10", "bottom:30", "40", "30");
  widget_on(ok, EVT_CLICK, on_click, "menu_up_left");
  
  ok = button_create(win, 0, 0, 0, 0);
  widget_set_tr_text(ok, "...");
  widget_set_self_layout_params(ok, "10", "top:30", "40", "30");
  widget_on(ok, EVT_CLICK, on_click, "menu_down_left");

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
