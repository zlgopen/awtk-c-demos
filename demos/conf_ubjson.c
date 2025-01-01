/**
 * File:   conf_ubjson.c
 * Author: AWTK Develop Team
 * Brief:  app conf demo
 *
 * Copyright (c) 2020 - 2025  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
 * 2020-06-07 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"
#include "conf_io/app_conf_init_ubjson.h"

static ret_t on_quit(void* ctx, event_t* e) {
  tk_quit();
  return RET_OK;
}

static ret_t window_main_open(void) {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* quit = button_create(win, 0, 0, 0, 0);

  locale_info_change(locale_info(), "zh", "CN");

  widget_set_tr_text(quit, "quit");
  widget_set_self_layout_params(quit, "center", "middle", "50%", "30");
  widget_on(quit, EVT_CLICK, on_quit, NULL);

  widget_layout(win);

  return RET_OK;
}

static ret_t app_conf_changed(void* ctx, event_t* e) {
  prop_change_event_t* evt = prop_change_event_cast(e);

  log_debug("%s changed\n", evt->name);

  return RET_OK;
}

ret_t application_init() {
  bool_t on = 0;
  int32_t port = 0;
  double timeout = 0;
  const char* name = NULL;

  app_conf_init_ubjson("conf");
  app_conf_on_changed(app_conf_changed, NULL);

  app_conf_set_bool("wifi.on", TRUE);
  assert(app_conf_exist("wifi.on"));

  app_conf_set_str("wifi.name", "awtk");
  assert(app_conf_exist("wifi.name"));

  app_conf_set_str("wifi.password", "123123");
  assert(app_conf_exist("wifi.password"));

  app_conf_remove("wifi.password");
  assert(!app_conf_exist("wifi.password"));

  app_conf_set_int("server.port", 8080);
  assert(app_conf_exist("server.port"));

  app_conf_set_double("server.timeout", 1.0);
  assert(app_conf_exist("server.timeout"));

  on = app_conf_get_bool("wifi.on", FALSE);
  assert(on == TRUE);

  port = app_conf_get_int("server.port", 0);
  assert(port == 8080);

  timeout = app_conf_get_double("server.timeout", 0);
  assert((timeout - 1.0) < 0.0001);

  name = app_conf_get_str("wifi.name", NULL);
  assert(tk_str_eq(name, "awtk"));

  app_conf_save();

  return window_main_open();
}

ret_t application_exit() {
  app_conf_deinit();
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
