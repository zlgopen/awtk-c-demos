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
 * 2018-08-16 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_dialog_btn_click(void* ctx, event_t* evt) {
  widget_t* win = widget_get_window(WIDGET(evt->target));
  int code = (char*)ctx - (char*)NULL;

  dialog_quit(win, code);

  return RET_OK;
}

static ret_t on_show_dialog(void* ctx, event_t* evt) {
  int code = 0;
  widget_t* ok = NULL;
  widget_t* cancel = NULL;
  widget_t* label = NULL;

  widget_t* dlg = dialog_create_simple(NULL, 0, 0, 240, 160);

  dialog_set_title(dlg, "Dialog");

  ok = button_create(dialog_get_client(dlg), 20, 80, 80, 30);
  widget_set_text(ok, L"Go");

  cancel = button_create(dialog_get_client(dlg), 140, 80, 80, 30);
  widget_set_text(cancel, L"Cancel");

  label = label_create(dialog_get_client(dlg), 10, 30, 200, 30);
  widget_set_text(label, L"AWTK is cool!");

  widget_on(ok, EVT_CLICK, on_dialog_btn_click, (char*)NULL + 1);
  widget_on(cancel, EVT_CLICK, on_dialog_btn_click, (char*)NULL + 2);

  code = dialog_modal(dlg);

  log_debug("code=%d\n", code);

  return RET_OK;
}

void application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* show_dialog = button_create(win, 0, 0, 0, 0);
  widget_t* show_dialog_long_press = button_create(win, 0, 0, 0, 0);

  widget_set_text(show_dialog, L"Show Dialog");
  widget_set_self_layout_params(show_dialog, "center", "middle:-30", "50%", "30");
  widget_on(show_dialog, EVT_CLICK, on_show_dialog, NULL);

  button_set_enable_long_press(show_dialog_long_press, TRUE);
  widget_set_text(show_dialog_long_press, L"Show Dialog On LongPress");
  widget_set_self_layout_params(show_dialog_long_press, "center", "middle:30", "80%", "30");
  widget_on(show_dialog_long_press, EVT_LONG_PRESS, on_show_dialog, NULL);

  widget_layout(win);
}

#include "demo_main.c"
