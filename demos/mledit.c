/**
 * File:   edit.c
 * Author: AWTK Develop Team
 * Brief:  edit demo
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

widget_t* create_edit(widget_t* win, int type, const char* name, const wchar_t* text, int x, int y,
                      int w, int h) {
  widget_t* edit = edit_create(win, x, y, w, h);


  widget_set_name(edit, name);
  widget_set_text(edit, text);

  return edit;
}

static ret_t on_click(void* ctx, event_t* e) {
  widget_t* edit1 = WIDGET(ctx);
  
  widget_set_text(edit1, L"中文　    a b c 123\nnext line");

  return RET_OK;
}

void application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  widget_t* edit1 = mledit_create(win, 0, 0, win->w, win->h/2);
  widget_t* button = button_create(win, 0, 0, 0, 0);

  widget_set_text(edit1, L"multi line edit");

  widget_set_text(button, L"SetText");
  widget_set_self_layout_params(button, "c", "b:60", "40%", "30");
  widget_on(button, EVT_CLICK, on_click, edit1);

  widget_layout(win);
}

#include "demo_main.c"
