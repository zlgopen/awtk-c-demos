﻿/**
 * File:   digit_clock.c
 * Author: AWTK Develop Team
 * Brief:  digit_clock demo
 *
 * Copyright (c) 2019 - 2025  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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

  widget_t* tc = digit_clock_create(win, 10, 10, 240, 30);
  digit_clock_set_format(tc, "YY/MM/DD h:mm:ss");

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
