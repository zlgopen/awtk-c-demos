/**
 * File:   edit.c
 * Author: AWTK Develop Team
 * Brief:  edit demo
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

static ret_t on_changed(void* ctx, event_t* evt) {
  widget_t* target = WIDGET(evt->target);

  log_debug("%s changed\n", target->name);

  return RET_OK;
}

static ret_t on_action_event(void* ctx, event_t* evt) {
  widget_t* target = WIDGET(evt->target);

  log_debug("%s action event\n", target->name);

  return RET_OK;
}

static ret_t on_changing(void* ctx, event_t* evt) {
  widget_t* target = WIDGET(evt->target);

  str_t str;
  str_init(&str, 0);
  str_from_wstr(&str, widget_get_text(target));
  log_debug("%s: %s\n", target->name, str.str);
  str_reset(&str);

  return RET_OK;
}

widget_t* create_edit(widget_t* win, int type, const char* name, const wchar_t* text, int x, int y,
                      int w, int h) {
  widget_t* edit = edit_create(win, x, y, w, h);

  widget_on(edit, EVT_VALUE_CHANGED, on_changed, NULL);
  widget_on(edit, EVT_VALUE_CHANGING, on_changing, NULL);
  edit_set_input_tips(edit, name);
  edit_set_input_type(edit, type);

  return edit;
}

static ret_t on_click(void* ctx, event_t* e) {
  widget_t* edit1 = WIDGET(ctx);

  widget_set_text(edit1,
                  L"中文 　  比 如 打 一 个 汉 字  加 一 个 空 格 再 打 一 个 汉 字   a b c 123");

  return RET_OK;
}

ret_t application_init() {
  widget_t* edit1 = NULL;
  widget_t* edit2 = NULL;
  widget_t* edit3 = NULL;
  widget_t* edit4 = NULL;
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* button = button_create(win, 0, 0, 0, 0);

  edit1 = create_edit(win, INPUT_TEXT, "text[3-32]", L"abc", 10, 10, 228, 30);
  widget_set_name(edit1, "edit1");
  edit_set_text_limit(edit1, 3, 32);
  edit_set_action_text(edit1, "Test");
  widget_on(edit1, EVT_IM_ACTION, on_action_event, NULL);

  edit_set_focus(edit1, TRUE);

  edit2 = create_edit(win, INPUT_INT, "int auto fix[1-100]", L"", 10, 50, 228, 30);
  widget_set_name(edit2, "edit2");
  edit_set_int_limit(edit2, 1, 100, 1);
  edit_set_auto_fix(edit2, TRUE);

  edit3 = create_edit(win, INPUT_FLOAT, "float[1-10]", L"1.23", 10, 90, 228, 30);
  widget_set_name(edit3, "edit3");
  edit_set_float_limit(edit3, 1, 10, 1);

  create_edit(win, INPUT_PASSWORD, "password", L"", 10, 10 + 128, 228, 30);
  widget_set_name(edit4, "edit4");
  edit4 = create_edit(win, INPUT_TEXT, "text", L"readonly", 10, 50 + 128, 228, 30);
  edit_set_readonly(edit4, TRUE);

  create_edit(win, INPUT_HEX, "hex", L"", 10, 90 + 128, 228, 30);
  create_edit(win, INPUT_CUSTOM, "custom", L"", 10, 130 + 128, 228, 30);

  widget_set_text(button, L"SetText");
  widget_set_self_layout_params(button, "c", "b:60", "40%", "30");
  widget_on(button, EVT_CLICK, on_click, edit1);

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
