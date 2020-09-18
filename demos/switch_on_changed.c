/**
 * File:   switch.c
 * Author: AWTK Develop Team
 * Brief:  switch demo
 *
 * Copyright (c) 2019 - 2020  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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

static ret_t on_will_change(void* ctx, event_t* e) {
  widget_t* win = WIDGET(ctx);
  widget_t* target = WIDGET(e->target);
  widget_t* sw1 = widget_lookup(win, "sw1", TRUE);
  widget_t* sw2 = widget_lookup(win, "sw2", TRUE);
  bool_t equal = widget_get_value(sw1) == widget_get_value(sw2);

  if (sw1 == target) {
    if(equal) {
      log_debug("prevent changed\n");
      return RET_STOP;
    }
  }

  if (sw2 == target) {
    if(!equal) {
      log_debug("prevent changed\n");
      return RET_STOP;
    }
  }

  return RET_OK;
}

static ret_t on_changed(void* ctx, event_t* e) {
  value_change_event_t* evt = value_change_event_cast(e);

  log_debug("on_changed: %d %d\n", 
      (int)value_bool(&(evt->old_value)), (int)value_bool(&(evt->new_value)));
  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* sw1 = switch_create(win, 0, 0, 0, 0);
  widget_t* sw2 = switch_create(win, 0, 0, 0, 0);

  widget_set_name(sw1, "sw1");
  widget_set_name(sw2, "sw2");
  switch_set_value(sw1, TRUE);
  switch_set_value(sw2, FALSE);

  widget_set_self_layout_params(sw1, "center:-80", "middle", "80", "30");
  widget_on(sw1, EVT_VALUE_WILL_CHANGE, on_will_change, win);
  widget_on(sw1, EVT_VALUE_CHANGED, on_changed, win);

  widget_set_self_layout_params(sw2, "center:80", "middle", "80", "30");
  widget_on(sw2, EVT_VALUE_WILL_CHANGE, on_will_change, win);
  widget_on(sw2, EVT_VALUE_CHANGED, on_changed, win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
