/**
 * File:   image_animation.c
 * Author: AWTK Develop Team
 * Brief:  image_animation demo
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

ret_t application_init() {
  widget_t* image_animation = NULL;
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  image_animation = image_animation_create(win, 10, 10, 200, 200);
  image_animation_set_image(image_animation, "ani");
  image_animation_set_interval(image_animation, 50);
  image_animation_set_range_sequence(image_animation, 1, 9);
  image_animation_play(image_animation);
  
  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
