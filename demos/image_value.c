/**
 * File:   image_value.c
 * Author: AWTK Develop Team
 * Brief:  image_value demo
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
 * 2019-01-14 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_timer_update(const timer_info_t* timer) {
  widget_t* win = WIDGET(timer->ctx);
  widget_t* image_value = widget_lookup(win, "image_value01", TRUE);

  image_value_set_value(image_value, IMAGE_VALUE(image_value)->value + 1);

  return RET_REPEAT;
}

ret_t application_init() {
  widget_t* image_value = NULL;
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  image_value = image_value_create(win, 10, 10, 200, 200);

  widget_set_name(image_value, "image_value01");
  image_value_set_image(image_value, "num_");
  image_value_set_value(image_value, 100);

  timer_add(on_timer_update, win, 1000);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
