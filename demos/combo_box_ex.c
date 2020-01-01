/**
 * File:   combo_box_ex.c
 * Author: AWTK Develop Team
 * Brief:  combo_box_ex demo
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

void application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* combo_box_ex1 = combo_box_ex_create(win, 0, 0, 0, 0);

  combo_box_set_options(combo_box_ex1, "1;2;3;4;5;6;7;8;9;10;11;12;13;14;15;16");
  combo_box_set_selected_index(combo_box_ex1, 1);
  widget_set_self_layout_params(combo_box_ex1, "center", "middle:-30", "50%", "30");

  widget_layout(win);
}

#include "demo_main.c"
