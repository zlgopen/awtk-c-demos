/**
 * File:   progress_circle.c
 * Author: AWTK Develop Team
 * Brief:  progress_circle demo
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
  widget_t* progress_circle = NULL;
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  progress_circle = progress_circle_create(win, 10, 10, 200, 200);
  progress_circle_set_max(progress_circle, 360);
  widget_set_value(progress_circle, 128);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
