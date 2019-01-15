/**
 * File:   slide_view.c
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
 * 2019-01-15 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

void application_init() {
  widget_t* view = NULL;
  widget_t* image = NULL;
  widget_t* slide_view = NULL;
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  slide_view = slide_view_create(win, 0, 0, win->w, win->h);

  view = image_create(slide_view, 0, 0, slide_view->w, slide_view->h);
  image = image_create(view, 0, 0, slide_view->w, slide_view->h);
  image_set_draw_type(image, IMAGE_DRAW_CENTER);
  image_set_image(image, "1");

  view = image_create(slide_view, 0, 0, slide_view->w, slide_view->h);
  image = image_create(view, 0, 0, slide_view->w, slide_view->h);
  image_set_draw_type(image, IMAGE_DRAW_CENTER);
  image_set_image(image, "2");
  
  view = image_create(slide_view, 0, 0, slide_view->w, slide_view->h);
  image = image_create(view, 0, 0, slide_view->w, slide_view->h);
  image_set_draw_type(image, IMAGE_DRAW_CENTER);
  image_set_image(image, "3");
}

#include "demo_main.c"
