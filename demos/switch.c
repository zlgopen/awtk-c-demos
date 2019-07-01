/**
 * File:   switch.c
 * Author: AWTK Develop Team
 * Brief:  switch demo
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

static ret_t on_changed(void* ctx, event_t* e) {
  log_debug("on_changed\n");
  return RET_OK;
}

void application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  widget_t* sw = switch_create(win, 10, 10, 80, 30);
  widget_on(sw, EVT_VALUE_CHANGED, on_changed, NULL);
}

#include "demo_main.c"
