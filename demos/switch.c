/**
 * File:   switch.c
 * Author: AWTK Develop Team
 * Brief:  switch demo
 *
 * Copyright (c) 2019 - 2021  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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

static ret_t on_changed(void* ctx, event_t* e) {
  value_change_event_t* evt =  value_change_event_cast(e);
  
  log_debug("on_changed %d => %d\n", value_int(&(evt->old_value)), value_int(&(evt->new_value)));

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  widget_t* sw = switch_create(win, 10, 10, 80, 30);
  widget_on(sw, EVT_VALUE_CHANGED, on_changed, NULL);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
