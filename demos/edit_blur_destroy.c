/**
 * File:   edit.c
 * Author: AWTK Develop Team
 * Brief:  edit demo
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

static ret_t on_blur(void* ctx, event_t* evt) {
  widget_t* target = WIDGET(evt->target);

  widget_destroy(target);

  return RET_OK;
}

widget_t* create_edit(widget_t* win, int type, const char* name, const wchar_t* text, int x, int y,
                      int w, int h) {
  widget_t* edit = edit_create(win, x, y, w, h);

  widget_set_name(edit, name);
  widget_set_text(edit, text);
  widget_on(edit, EVT_BLUR, on_blur, edit);

  edit_set_input_tips(edit, name);
  edit_set_input_type(edit, type);

  return edit;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  widget_t* edit = create_edit(win, INPUT_TEXT, "text[3-32]", L"abc", 10, 10, 228, 30);
  edit = create_edit(win, INPUT_TEXT, "text[3-32]", L"abc", 10, 60, 228, 30);

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
