/**
 * File:   5keys.c
 * Author: AWTK Develop Team
 * Brief:  用于支持只有方向键和OK键的情况。
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
 * 2021-06-15 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

/*
 * 为支持只有方向键和OK键的硬件，我们设置一个二值状态:
 *
 * moving_focus_mode
 *
 * TRUE: 移动焦点模式。此时方向键用于切换焦点。
 * FALSE: 非移动焦点模式。此时方向键直接传递给控件，用于修改控件的值。
 *
 * 通过RETURN键在两种模式之间切换。
 */
#define WIDGET_PROP_MOVING_FOCUS_MODE "moving_focus_mode"

#ifdef WITH_3KEYS_MODE
/*3键：上下键+回车键*/
#define widget_focus_up_prev(w) widget_focus_prev(w)
#define widget_focus_down_next(w) widget_focus_next(w)
#else
/*5键：上下左右键+回车键*/
#define widget_focus_up_prev(w) widget_focus_up(w)
#define widget_focus_down_next(w) widget_focus_down(w)
#endif/*WITH_3KEYS_MODE*/

static ret_t window_on_keydown_before_children(void* ctx, event_t* e) {
  widget_t* win = WIDGET(ctx);
  key_event_t* evt = key_event_cast(e);
  widget_t* focus = widget_get_focused_widget(win);
  bool_t moving_focus_mode = widget_get_prop_bool(win, WIDGET_PROP_MOVING_FOCUS_MODE, FALSE);

  if (focus != NULL) {
    if (focus->vt->return_key_to_activate) {
      /*对于按钮等通过回车键激活控件，方向键始终用于切换焦点*/
      widget_set_prop_bool(win, WIDGET_PROP_MOVING_FOCUS_MODE, TRUE);
    } else {
      /*其它控件，回车键用于切换模式*/
      if (evt->key == TK_KEY_RETURN) {
        widget_set_prop_bool(win, WIDGET_PROP_MOVING_FOCUS_MODE, !moving_focus_mode);
        log_debug("change moving_focus_mode:%d\n", !moving_focus_mode);
        return RET_OK;
      }
    }

    if (moving_focus_mode) {
      switch (evt->key) {
        case TK_KEY_LEFT: {
          widget_focus_left(focus);
          return RET_STOP;
        }
        case TK_KEY_RIGHT: {
          widget_focus_right(focus);
          return RET_STOP;
        }
        case TK_KEY_UP: {
          widget_focus_up_prev(focus);
          return RET_STOP;
        }
        case TK_KEY_DOWN: {
          widget_focus_down_next(focus);
          return RET_STOP;
        }
        default:
          break;
      }
    }
  }

  return RET_OK;
}

ret_t window_enable_5keys_mode(widget_t* win) {
  widget_on(win, EVT_KEY_DOWN_BEFORE_CHILDREN, window_on_keydown_before_children, win);

  return RET_OK;
}
/****************************************/

static ret_t on_inc(void* ctx, event_t* e) {
  widget_t* value = widget_lookup(WIDGET(ctx), "value", TRUE);

  widget_add_value(value, 1);

  return RET_OK;
}

static ret_t on_dec(void* ctx, event_t* e) {
  widget_t* value = widget_lookup(WIDGET(ctx), "value", TRUE);

  widget_add_value(value, -1);

  return RET_OK;
}

static ret_t on_reset(void* ctx, event_t* e) {
  widget_t* value = widget_lookup(WIDGET(ctx), "value", TRUE);
  widget_set_value(value, 0);

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_open("5keys");

  widget_child_on(win, "inc", EVT_CLICK, on_inc, win);
  widget_child_on(win, "dec", EVT_CLICK, on_dec, win);
  widget_child_on(win, "reset", EVT_CLICK, on_reset, win);

  window_enable_5keys_mode(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
