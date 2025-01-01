/**
 * File:   file_pick.c
 * Author: AWTK Develop Team
 * Brief:  file pick
 *
 * Copyright (c) 2024 - 2025  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
 * 2024-12-03 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"
#include "file_browser/file_dialog.h"

static ret_t on_pick_click(void* ctx, event_t* e) {
  widget_t* win = WIDGET(ctx);
  char* filename = tk_choose_file("*.txt;*.c;*.h", "demos");

  log_debug("pick: %s\n", filename);
  widget_set_child_text_utf8(win, "result", filename);

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* pick = button_create(win, 0, 0, 0, 0);
  widget_t* result = label_create(win, 0, 0, 0, 0);

  widget_set_text_utf8(pick, "Pick File...");
  widget_set_self_layout(pick, "default(x=c,y=m,w=50%,h=30)");
  widget_on(pick, EVT_CLICK, on_pick_click, win);

  widget_set_name(result, "result");
  widget_set_self_layout(result, "default(x=c,y=m:40,w=80%,h=30)");

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
