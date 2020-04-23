/**
 * File:   progress_bar.c
 * Author: AWTK Develop Team
 * Brief:  progress_bar demo
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
 * 2018-08-17 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_changed(void* ctx, event_t* evt) {
  widget_t* target = WIDGET(evt->target);

  log_debug("%s changed\n", target->name);

  return RET_OK;
}

widget_t* create_progress_bar(widget_t* win, bool_t vertical, const char* name) {
  widget_t* progress_bar = progress_bar_create(win, 0, 0, 0, 0);

  widget_on(progress_bar, EVT_VALUE_CHANGED, on_changed, NULL);

  widget_set_name(progress_bar, name);
  progress_bar_set_value(progress_bar, 10);
  progress_bar_set_vertical(progress_bar, vertical);

  if (vertical) {
    widget_set_self_layout_params(progress_bar, "center", "10", "20", "80%");
  } else {
    widget_set_self_layout_params(progress_bar, "center", "bottom:10", "90%", "20");
  }

  return progress_bar;
}

static ret_t on_timer(const timer_info_t* info) {
  widget_t* win = WIDGET(info->ctx);
  progress_bar_t* bar1 = PROGRESS_BAR(widget_child(win, "bar1"));
  progress_bar_t* bar2 = PROGRESS_BAR(widget_child(win, "bar2"));

  if (bar1->value < 100) {
    progress_bar_set_value(WIDGET(bar1), bar1->value + 5);
    progress_bar_set_value(WIDGET(bar2), bar2->value + 5);

    return RET_REPEAT;
  } else {
    return RET_REMOVE;
  }
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  create_progress_bar(win, FALSE, "bar1");
  create_progress_bar(win, TRUE, "bar2");

  widget_add_timer(win, on_timer, 500);

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
