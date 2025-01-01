/**
 * File:   combo_box.c
 * Author: AWTK Develop Team
 * Brief:  combo_box demo
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

static widget_t* custom_open_popup(widget_t* combo_box) {
  return window_open("color");
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* combo_box1 = combo_box_create(win, 0, 0, 0, 0);
  widget_t* combo_box2 = combo_box_create(win, 0, 0, 0, 0);

  combo_box_set_options(combo_box1, "left;center;right;");
  combo_box_set_selected_index(combo_box1, 1);
  widget_set_self_layout_params(combo_box1, "center", "middle:-30", "50%", "30");

  combo_box_set_custom_open_popup(combo_box2, custom_open_popup, NULL);
  widget_set_self_layout_params(combo_box2, "center", "middle:30", "50%", "30");

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
