/**
 * File:   time_clock.c
 * Author: AWTK Develop Team
 * Brief:  time_clock demo
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

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  widget_t* tc = time_clock_create(win, 10, 10, 240, 240);
  time_clock_set_image(tc, "clock");
  time_clock_set_bg_image(tc, "clock_bg");
  time_clock_set_hour_image(tc, "clock_hour");
  time_clock_set_minute_image(tc, "clock_minute");
  time_clock_set_second_image(tc, "clock_second");

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
