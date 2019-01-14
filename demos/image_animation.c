/**
 * File:   image.c
 * Author: AWTK Develop Team
 * Brief:  image demo
 *
 * Copyright (c) 2018 - 2019  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
  widget_t* image_animation = NULL;
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  image_animation = image_animation_create(win, 10, 10, 200, 200);
  image_animation_set_image(image_animation, "ani");
  image_animation_set_interval(image_animation, 50);
  image_animation_set_sequence(image_animation, "123456789abc");
  image_animation_play(image_animation);
}

#include "demo_main.c"
