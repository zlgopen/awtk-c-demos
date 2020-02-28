/**
 * File:   clip_view.c
 * Author: AWTK Develop Team
 * Brief:  clip_view demo
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
 * 2019-12-12 Luo ZhiMing <luozhiming@zlg.cn> created
 *
 */

#include "awtk.h"
#include "base/image_base.h"

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* view = view_create(win, 0, 0, win->w / 2, win->h / 2);
  widget_t* clip_view = clip_view_create(view, 0, 0, 0, 0);
  widget_t* button = button_create(clip_view, 0, 0, 0, 0);
  widget_t* image = image_create(clip_view, 0, 50, 800, 600);

  widget_t* view1 = view_create(win, win->w / 2, win->h / 2, win->w / 2, win->h / 2);
  widget_t* clip_view1 = clip_view_create(view1, 0, 0, 0, 0);
  widget_t* button1 = button_create(clip_view1, 0, 0, 0, 0);
  widget_t* image1 = image_create(clip_view1, -700, -450, 800, 600);

  widget_set_self_layout_params(clip_view, "0", "0", "100%", "100%");
  widget_set_self_layout_params(clip_view1, "0", "0", "100%", "100%");

  widget_set_self_layout_params(button, "50%", "10", "60%", "35");
  widget_set_self_layout_params(button1, "50%", "b:40", "60%", "35");

  widget_set_text_utf8(button, "abcdefghimn");
  widget_set_text_utf8(button1, "abcdefghimn");

  image_set_image(image, "bg_landscape_1");
  image_set_image(image1, "bg_landscape_1");

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
