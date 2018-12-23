/**
 * File:   combo_box.c
 * Author: AWTK Develop Team
 * Brief:  combo_box demo
 *
 * Copyright (c) 2018 - 2018  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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

void application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* combo_box = combo_box_create(win, 0, 0, 0, 0);

  combo_box_set_options(combo_box, "left;center;right;");
  combo_box_set_selected_index(combo_box, 1);
  widget_set_self_layout_params(combo_box, "center", "middle", "50%", "30");

  widget_layout(win);
}

#include "demo_main.c"
