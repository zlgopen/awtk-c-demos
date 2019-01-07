/**
 * File:   slider.c
 * Author: AWTK Develop Team
 * Brief:  slider demo
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
 * 2018-08-16 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_changed(void* ctx, event_t* evt) {
  widget_t* target = WIDGET(evt->target);

  log_debug("%s changed\n", target->name);

  return RET_OK;
}

static ret_t on_changing(void* ctx, event_t* evt) {
  widget_t* target = WIDGET(evt->target);

  log_debug("%s changing\n", target->name);

  return RET_OK;
}

widget_t* create_progress_bar(widget_t* win, bool_t vertical, const char* name) {
  widget_t* slider = slider_create(win, 0, 0, 0, 0);

  widget_on(slider, EVT_VALUE_CHANGED, on_changed, NULL);
  widget_on(slider, EVT_VALUE_CHANGING, on_changing, NULL);

  widget_set_name(slider, name);
  slider_set_value(slider, 10);
  slider_set_vertical(slider, vertical);

  if (vertical) {
    widget_set_self_layout_params(slider, "center", "10", "20", "80%");
  } else {
    widget_set_self_layout_params(slider, "center", "bottom:10", "90%", "20");
  }

  return slider;
}

void application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  create_progress_bar(win, FALSE, "slider1");
  create_progress_bar(win, TRUE, "slider2");

  widget_layout(win);
}

#include "demo_main.c"
