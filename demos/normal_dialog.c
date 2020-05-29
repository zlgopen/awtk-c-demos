/**
 * File:   dialog.c
 * Author: AWTK Develop Team
 * Brief:  normal dialog demo
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
 * 2020-05-29 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_yes(void* ctx, event_t* e) {
  tk_quit();

  return RET_OK;
}

static ret_t on_no(void* ctx, event_t* e) {
  window_close(widget_get_window(WIDGET(e->target)));

  return RET_OK;
}

static ret_t on_open_dialog(void* ctx, event_t* e) {
  widget_t* ok = NULL;
  widget_t* cancel = NULL;
  widget_t* label = NULL;
  widget_t* dlg = dialog_create_simple(NULL, 0, 0, 240, 160);

  dialog_set_title(dlg, "Dialog");

  ok = button_create(dialog_get_client(dlg), 20, 80, 80, 30);
  widget_on(ok, EVT_CLICK, on_yes, NULL);
  widget_set_text(ok, L"Yes");

  cancel = button_create(dialog_get_client(dlg), 140, 80, 80, 30);
  widget_on(cancel, EVT_CLICK, on_no, NULL);
  widget_set_text(cancel, L"No");

  label = label_create(dialog_get_client(dlg), 10, 30, 200, 30);
  widget_set_text(label, L"Are you sure to quit?");

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* ok = button_create(win, 0, 0, 0, 0);

  locale_info_change(locale_info(), "zh", "CN");

  widget_set_tr_text(ok, "ok");
  widget_set_self_layout_params(ok, "center", "middle", "50%", "30");
  widget_on(ok, EVT_CLICK, on_open_dialog, NULL);

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
