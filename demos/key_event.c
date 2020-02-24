/**
 * File:   button.c
 * Author: AWTK Develop Team
 * Brief:  button demo
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
 * 2018-08-16 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_click(void* ctx, event_t* e) {
  dialog_toast("Press Q Quit", 3000);

  return RET_OK;
}

static ret_t press_q_to_quit(void* ctx, event_t* e) {
  key_event_t* evt = key_event_cast(e);

  if(evt->key == TK_KEY_q || evt->key == TK_KEY_Q) {
    if(dialog_confirm("Confirm", "Are you to quit?") == RET_OK) {
      tk_quit();
    }
  }

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* quit = button_create(win, 0, 0, 0, 0);

  widget_set_text(quit, L"Press Q Quit");
  widget_set_prop_bool(quit, WIDGET_PROP_FOCUSABLE, TRUE);
  widget_set_prop_bool(quit, WIDGET_PROP_FOCUSED, TRUE);
  widget_set_self_layout_params(quit, "center", "middle", "50%", "40");

  widget_on(quit, EVT_CLICK, on_click, NULL);
  widget_on(quit, EVT_KEY_DOWN, press_q_to_quit, NULL);

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"

