/**
 * File:   image.c
 * Author: AWTK Develop Team
 * Brief:  image demo
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
 * 2018-08-16 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

widget_t* create_image(widget_t* win, const char* image_name, image_draw_type_t draw_type) {
  widget_t* image = image_create(win, 0, 0, 0, 0);

  widget_use_style(image, "border");
  image_set_draw_type(image, draw_type);
  image_set_image(image, image_name);

  return image;
}

ret_t application_init() {
  widget_t* image = NULL;
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  image = create_image(win, "earth", IMAGE_DRAW_ICON);
  image_set_rotation(image, 0.5);
  image_set_scale(image, 1, 2);

  image = create_image(win, "earth", IMAGE_DRAW_CENTER);
  image = create_image(win, "earth", IMAGE_DRAW_SCALE_AUTO);

  image = create_image(win, "1", IMAGE_DRAW_SCALE);
  image = create_image(win, "2", IMAGE_DRAW_SCALE_W);
  image = create_image(win, "3", IMAGE_DRAW_SCALE_H);

  image = create_image(win, "bricks", IMAGE_DRAW_REPEAT);
  image = create_image(win, "bricks", IMAGE_DRAW_REPEAT_X);
  image = create_image(win, "bricks", IMAGE_DRAW_REPEAT_Y);

  widget_set_children_layout(win, "default(r=3,c=3,m=2,s=2)");
  widget_layout(win);
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
