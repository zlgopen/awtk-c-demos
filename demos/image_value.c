/**
 * File:   image_value.c
 * Author: AWTK Develop Team
 * Brief:  image_value demo
 *
 * Copyright (c) 2019 - 2019  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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

void application_init() {
  widget_t* image_value = NULL;
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  image_value = image_value_create(win, 10, 10, 200, 200);
  image_value_set_image(image_value, "num_");
  image_value_set_value(image_value, 100);
}

#include "demo_main.c"
