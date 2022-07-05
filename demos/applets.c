/**
 * File:   apps.c
 * Author: AWTK Develop Team
 * Brief:  apps
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
 * 2022-07-04 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_click(void* ctx, event_t* e) {
  window_open((const char*)ctx);

  return RET_OK;
}

static ret_t on_click_theme(void* ctx, event_t* e) {
  widget_t* widget = WIDGET(e->target);
  widget_set_theme(widget, (const char*)ctx);

  return RET_OK;
}

ret_t application_init() {
  window_open("system_bar");
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* foo = button_create(win, 0, 0, 0, 0);
  widget_t* bar = button_create(win, 0, 0, 0, 0);
  widget_t* dark_theme = button_create(win, 0, 0, 0, 0);
  widget_t* default_theme = button_create(win, 0, 0, 0, 0);

  widget_set_text_utf8(foo, "foo");
  widget_set_self_layout_params(foo, "center:-60", "middle", "80", "30");
  widget_on(foo, EVT_CLICK, on_click, (void*)"foo.main");
  
  widget_set_text_utf8(bar, "bar");
  widget_set_self_layout_params(bar, "center:60", "middle", "80", "30");
  widget_on(bar, EVT_CLICK, on_click, (void*)"bar.main");
  
  widget_set_text_utf8(default_theme, "default_theme");
  widget_set_self_layout_params(default_theme, "center:80", "bottom:20", "128", "30");
  widget_on(default_theme, EVT_CLICK, on_click_theme, (void*)"default");
  
  widget_set_text_utf8(dark_theme, "dark_theme");
  widget_set_self_layout_params(dark_theme, "center:-80", "bottom:20", "128", "30");
  widget_on(dark_theme, EVT_CLICK, on_click_theme, (void*)"dark");

  assets_managers_set_applet_res_root("applets/");

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
