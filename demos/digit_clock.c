/**
 * File:   digit_clock.c
 * Author: AWTK Develop Team
 * Brief:  digit_clock demo
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

void application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  widget_t* tc = digit_clock_create(win, 10, 10, 240, 30);
  digit_clock_set_format(tc, "YY/MM/DD h:mm:ss");
}

#include "demo_main.c"
