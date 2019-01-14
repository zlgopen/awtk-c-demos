/**
 * File:   gif_image.c
 * Author: AWTK Develop Team
 * Brief:  gif image demo
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
  widget_t* image = NULL;
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  image = gif_image_create(win, 10, 10, 200, 200);
  image_set_image(image, "bee");
}

#include "demo_main.c"
