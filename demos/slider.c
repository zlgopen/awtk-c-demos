/**
 * File:   slider.c
 * Author: AWTK Develop Team
 * Brief:  slider demo
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
 * 2018-08-16 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_changed(void* ctx, event_t* evt) {
  widget_t* target = WIDGET(evt->target);
  slider_t* slider = SLIDER(target);

  log_debug("%s changed: [min=%lf max=%lf step=%lf value=%lf]\n", target->name, slider->min,
            slider->max, slider->step, slider->value);

  return RET_OK;
}

static ret_t on_changing(void* ctx, event_t* evt) {
  widget_t* target = WIDGET(evt->target);
  slider_t* slider = SLIDER(target);

  log_debug("%s changing: [min=%lf max=%lf step=%lf value=%lf]\n", target->name, slider->min,
            slider->max, slider->step, slider->value);

  return RET_OK;
}

widget_t* create_progress_bar(widget_t* win, bool_t vertical, const char* name) {
  widget_t* slider = slider_create(win, 0, 0, 0, 0);

  widget_on(slider, EVT_VALUE_CHANGED, on_changed, NULL);
  widget_on(slider, EVT_VALUE_CHANGING, on_changing, NULL);

  widget_set_name(slider, name);
  slider_set_vertical(slider, vertical);

  return slider;
}

ret_t application_init() {
  widget_t* slider = NULL;
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  slider = create_progress_bar(win, FALSE, "slider1");
  widget_set_self_layout_params(slider, "center", "bottom:10", "90%", "20");

  slider = create_progress_bar(win, TRUE, "slider2");
  widget_set_self_layout_params(slider, "center", "10", "20", "80%");
  slider_set_min(slider, 0);
  slider_set_max(slider, 100);
  slider_set_step(slider, 0);
  slider_set_value(slider, 10);

  slider = create_progress_bar(win, TRUE, "slider3");
  widget_set_self_layout_params(slider, "center:-60", "10", "20", "80%");
  slider_set_min(slider, -100);
  slider_set_max(slider, 100);
  slider_set_step(slider, 10);
  slider_set_value(slider, 10);

  slider = create_progress_bar(win, TRUE, "slider4");
  widget_set_self_layout_params(slider, "center:60", "10", "20", "80%");
  slider_set_min(slider, -1);
  slider_set_max(slider, 1);
  slider_set_step(slider, 0.1f);
  slider_set_value(slider, 0);

  slider = create_progress_bar(win, TRUE, "slider5");
  widget_set_self_layout_params(slider, "center:-100", "10", "20", "80%");
  slider_set_min(slider, -10);
  slider_set_max(slider, 0);
  slider_set_step(slider, 1);
  slider_set_value(slider, 0);

  slider = create_progress_bar(win, TRUE, "slider6");
  widget_set_self_layout_params(slider, "center:100", "10", "20", "80%");
  slider_set_min(slider, 0);
  slider_set_max(slider, 10);
  slider_set_step(slider, 1);
  slider_set_value(slider, 5);

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
