/**
 * File:   mutable_image.c
 * Author: AWTK Develop Team
 * Brief:  mutable image demo
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
 * 2019-02-28 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static color_t s_bg_color;

static ret_t dummy_prepare_image(void* ctx, bitmap_t* image) {
  rect_t r = rect_init(0, 0, image->w, image->h);
  image_fill(image, &r, s_bg_color);

  if (s_bg_color.rgba.r < 0xff) {
    s_bg_color.rgba.r++;
  } else if (s_bg_color.rgba.g < 0xff) {
    s_bg_color.rgba.g++;
  } else if (s_bg_color.rgba.b < 0xff) {
    s_bg_color.rgba.b++;
  } else {
    s_bg_color.rgba.r = 0;
    s_bg_color.rgba.g = 0;
    s_bg_color.rgba.b = 0;
  }

  return RET_OK;
}

void application_init() {
  widget_t* image = NULL;
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  s_bg_color = color_init(0, 0, 0, 0xff);
  image = mutable_image_create(win, 0, 0, win->w, win->h);
  mutable_image_set_prepare_image(image, dummy_prepare_image, &s_bg_color);

  window_manager_set_show_fps(win->parent, TRUE);
}

#include "demo_main.c"
