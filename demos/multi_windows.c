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
  widget_set_text(label, L"Press F2/F3 To CLose");
  widget_set_self_layout_params(label, "center", "middle", "100%", "30");

  widget_layout(win);

  return RET_OK;
}

static ret_t on_key_back_or_back_to_home(void* ctx, event_t* e) {
  key_event_t* evt = (key_event_t*)e;
  if (evt->key == TK_KEY_F2) {
    window_manager_back(WIDGET(ctx));
  } else if (evt->key == TK_KEY_F3) {
    window_manager_back_to_home(WIDGET(ctx));
  }

  return RET_OK;
}

void application_init() {
  widget_t* wm = window_manager();
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* open_window = button_create(win, 0, 0, 0, 0);

  widget_set_prop_str(win, WIDGET_PROP_CLOSABLE, "no");

  widget_set_text(open_window, L"Open Window");
  widget_set_self_layout_params(open_window, "center", "middle", "50%", "30");
  widget_on(open_window, EVT_CLICK, on_open_window, NULL);

  widget_layout(win);

  widget_on(wm, EVT_KEY_DOWN, on_key_back_or_back_to_home, wm);
}

#include "demo_main.c"
