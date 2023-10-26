/**
 * File:   packed_image.c
 * Author: AWTK Develop Team
 * Brief:  packed image demo
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
 * 2023-10-26 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_demo1(void* ctx, event_t* e) {
  image_set_image(WIDGET(ctx), "bg_portrait_2#xywh(10,20,100,80)");

  return RET_OK;
}

static ret_t on_demo2(void* ctx, event_t* e) {
  image_set_image(WIDGET(ctx), "bg_portrait_2#grid(4,4,1,2)");

  return RET_OK;
}

static ret_t on_restore(void* ctx, event_t* e) {
  image_set_image(WIDGET(ctx), "bg_portrait_2");

  return RET_OK;
}

static ret_t on_quit(void* ctx, event_t* e) {
  tk_quit();
  return RET_OK;
}

ret_t application_init() {
  widget_t* image = NULL;
  widget_t* button = NULL;
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  image = image_create(win, 0, 0, win->w, win->h/2);
  image_set_image(image, "bg_portrait_2");
  image_set_draw_type(image, IMAGE_DRAW_DEFAULT);

  button = button_create(win, 0, 0, 0, 0);
  widget_set_text_utf8(button, "demo1");
  widget_set_self_layout_params(button, "c", "m:30", "128", "30");
  widget_on(button, EVT_CLICK, on_demo1, image);

  button = button_create(win, 0, 0, 0, 0);
  widget_set_text_utf8(button, "demo2");
  widget_set_self_layout_params(button, "c", "m:80", "128", "30");
  widget_on(button, EVT_CLICK, on_demo2, image);
  
  button = button_create(win, 0, 0, 0, 0);
  widget_set_text_utf8(button, "restore");
  widget_set_self_layout_params(button, "c", "m:130", "128", "30");
  widget_on(button, EVT_CLICK, on_restore, image);
  
  button = button_create(win, 0, 0, 0, 0);
  widget_set_text_utf8(button, "quit");
  widget_set_self_layout_params(button, "c", "m:180", "128", "30");
  widget_on(button, EVT_CLICK, on_quit, NULL);

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
