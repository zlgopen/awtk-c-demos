/**
 * File:   dialog.c
 * Author: AWTK Develop Team
 * Brief:  dialog demo
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
 * 2019-03-04 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_open_window(void* ctx, event_t* evt) {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* label = label_create(win, 0, 0, 0, 0);
  
  widget_set_prop_str(win, WIDGET_PROP_ANIM_HINT, "htranslate");
  widget_set_text(label, L"Press Escape To CLose");
  widget_set_self_layout_params(label, "center", "middle", "100%", "30");

  widget_layout(win);

  return RET_OK;
}

static ret_t wm_on_key_down(void* ctx, event_t* e) {
  key_event_t* evt = (key_event_t*)e;
  if (evt->key == TK_KEY_ESCAPE) {
    window_manager_request_close_top_window(WIDGET(ctx));
  }

  return RET_OK;
}

void application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* open_window = button_create(win, 0, 0, 0, 0);

  widget_set_prop_str(win, WIDGET_PROP_CLOSABLE, "no");

  widget_set_text(open_window, L"Open Window");
  widget_set_self_layout_params(open_window, "center", "middle", "50%", "30");
  widget_on(open_window, EVT_CLICK, on_open_window, NULL);

  widget_layout(win);

  widget_on(window_manager(), EVT_KEY_DOWN, wm_on_key_down, window_manager());
}

#include "demo_main.c"
