/**
 * File:   edit.c
 * Author: AWTK Develop Team
 * Brief:  edit demo
 *
 * Copyright (c) 2018 - 2018  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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

#include "base/edit.h"
#include "base/window.h"

static ret_t on_changed(void* ctx, event_t* evt) {
  widget_t* target = WIDGET(evt->target);

  log_debug("%s changing\n", target->name);

  return RET_OK;
}

static ret_t on_changing(void* ctx, event_t* evt) {
  widget_t* target = WIDGET(evt->target);

  log_debug("%s changing\n", target->name);

  return RET_OK;
}

widget_t* create_edit(widget_t* win, int type, const char* name, const char* text, int x, int y,
                      int w, int h) {
  widget_t* edit = edit_create(win, x, y, w, h);

  widget_on(edit, EVT_VALUE_CHANGED, on_changed, NULL);
  widget_on(edit, EVT_VALUE_CHANGING, on_changing, NULL);

  widget_set_name(edit, name);
  widget_set_text_utf8(edit, text);

  edit_set_input_tips(edit, name);
  edit_set_input_type(edit, type);

  return edit;
}

void application_init() {
  widget_t* edit1 = NULL;
  widget_t* edit2 = NULL;
  widget_t* edit3 = NULL;
  widget_t* edit4 = NULL;
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  edit1 = create_edit(win, INPUT_TEXT, "text[3-8]", "", 10, 10, 228, 30);
  edit_set_text_limit(edit1, 3, 8);

  edit2 = create_edit(win, INPUT_INT, "int auto fix[1-100]", "", 10, 50, 228, 30);
  edit_set_int_limit(edit2, 1, 100, 1);
  edit_set_auto_fix(edit2, TRUE);

  edit3 = create_edit(win, INPUT_FLOAT, "float[1-10]", "1.23", 10, 90, 228, 30);
  edit_set_float_limit(edit3, 1, 10, 1);

  create_edit(win, INPUT_PASSWORD, "password", "", 10, 10 + 128, 228, 30);
  edit4 = create_edit(win, INPUT_TEXT, "text", "readonly", 10, 50 + 128, 228, 30);
  edit_set_readonly(edit4, TRUE);

  create_edit(win, INPUT_HEX, "hex", "", 10, 90 + 128, 228, 30);
  create_edit(win, INPUT_EMAIL, "email", "", 10, 130 + 128, 228, 30);

  widget_layout(win);
}

#include "demo_main.c"
