/**
 * File:   label.c
 * Author: AWTK Develop Team
 * Brief:  label demo
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
 * 2018-08-15 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* label = label_create(win, 0, 0, 0, 0);

  widget_use_style(label, "big_green");
  widget_set_text(label, L"hello awtk!");
  widget_set_self_layout_params(label, "center", "middle", "50%", "30");

  widget_layout(win);

  return RET_OK;
}

#include "demo_main.c"
