/**
 * File:   unload_image.c
 * Author: AWTK Develop Team
 * Brief:  unload image
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
 * 2018-12-19 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_clear_image(void* ctx, event_t* e) {
  widget_t* button = WIDGET(e->target);
  image_manager_t* im = widget_get_image_manager(button);

  image_manager_unload_unused(im, 0);
  log_debug("unload image done\n");

  return RET_OK;
}

static ret_t on_quit(void* ctx, event_t* e) {
  tk_quit();
  return RET_OK;
}

void application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* button = button_create(win, 0, 0, 0, 0);
  widget_t* image = image_create(win, 0, 0, 0, 0);
 
  image_set_image(image, "file://"APP_ROOT"/demos/zh.png");
  widget_set_self_layout_params(image, "center", "middle:-100", "100", "100");
  
  image = image_create(win, 0, 0, 0, 0);
  image_set_image(image, "earth");
  widget_set_self_layout_params(image, "center", "middle:-50", "100", "100");

  widget_set_text(button, L"clear image");
  widget_set_self_layout_params(button, "center", "middle", "50%", "30");
  widget_on(button, EVT_CLICK, on_clear_image, NULL);
  
  button = button_create(win, 0, 0, 0, 0);
  widget_set_text(button, L"quit");
  widget_set_self_layout_params(button, "center", "middle:60", "50%", "30");
  widget_on(button, EVT_CLICK, on_quit, NULL);

  widget_layout(win);
}

#include "demo_main.c"
