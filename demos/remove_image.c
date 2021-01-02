/**
 * File:   remove_image.c
 * Author: AWTK Develop Team
 * Brief:  remove_image demo
 *
 * Copyright (c) 2018 - 2021  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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

static ret_t on_click(void* ctx, event_t* e) {
  widget_t* image = WIDGET(ctx);

  image_set_image(image, "");

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* ok = button_create(win, 0, 0, 0, 0);
  widget_t* image = image_create(win, 0, 0, 0, 0);

  widget_set_text(ok, L"Remove");
  widget_set_self_layout_params(ok, "center", "bottom:10", "50%", "30");
  widget_set_self_layout_params(image, "center", "middle", "100", "100");
  widget_on(ok, EVT_CLICK, on_click, image);
  image_set_image(image, "earth");
  widget_set_text(image, L"earth");

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
