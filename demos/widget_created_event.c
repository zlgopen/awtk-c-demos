/**
 * File:   basic.c
 * Author: AWTK Develop Team
 * Brief:  demo for open window and install event handlers
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
 * 2018-08-18 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_widget_created(void* ctx, event_t* e) {
  widget_t* widget = WIDGET(e->target);
  widget_t* win = widget_get_window(widget);

  log_debug("%s widget %s created\n", win->name, widget_get_type(widget));

  return RET_OK;
}

ret_t application_init() {
  emitter_t* emitter = EMITTER(widget_factory());
  uint32_t id = emitter_on(emitter, EVT_WIDGET_CREATED, on_widget_created, NULL);

  window_open("basic");

  emitter_off(emitter, id);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
