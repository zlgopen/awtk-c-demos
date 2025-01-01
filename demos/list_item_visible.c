/**
 * File:   basic.c
 * Author: AWTK Develop Team
 * Brief:  demo for open window and install event handlers
 *
 * Copyright (c) 2018 - 2025  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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

static ret_t on_timer(const timer_info_t* timer) {
  widget_t* view = WIDGET(timer->ctx);
  widget_t* item = widget_get_child(view, 0);

  widget_set_visible(item, !(item->visible), TRUE);
  widget_invalidate_force(view, NULL);

  return RET_REPEAT;
}

ret_t application_init() {
  widget_t* win = window_open("list_view_m");
  widget_t* view = widget_lookup_by_type(win, WIDGET_TYPE_SCROLL_VIEW, TRUE);

  timer_add(on_timer, view, 1000);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
