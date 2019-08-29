/**
 * File:   mledit.c
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

static ret_t on_click_set_text(void* ctx, event_t* e) {
  widget_t* mledit = WIDGET(ctx);

  widget_set_text(mledit, L"中文　    a b c 123\nnext line");

  return RET_OK;
}

static ret_t on_click_close(void* ctx, event_t* e) {
  window_close(WIDGET(ctx));
  return RET_OK;
}

static ret_t create_new_window(const char* anim) {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* close = button_create(win, 0, 0, 0, 0);

  widget_set_prop_str(win, WIDGET_PROP_ANIM_HINT, anim);
  widget_set_text(close, L"Close");
  widget_set_self_layout_params(close, "c", "b:60", "40%", "30");
  widget_on(close, EVT_CLICK, on_click_close, win);

  return RET_OK;
}

static ret_t on_click_open_window_with_anim(void* ctx, event_t* e) {
  create_new_window("htranslate");
  return RET_OK;
}

static ret_t on_click_open_window_without_anim(void* ctx, event_t* e) {
  create_new_window(NULL);
  return RET_OK;
}

static ret_t on_window_to_background(void* ctx, event_t* e) {
  log_debug("on_window_to_background\n");
  return RET_OK;
}

static ret_t on_window_to_foreground(void* ctx, event_t* e) {
  widget_t* mledit = widget_lookup(WIDGET(ctx), "mledit", TRUE);

  mledit_set_focus(mledit, TRUE);
  log_debug("on_window_to_foreground\n");
  return RET_OK;
}

void application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  widget_t* mledit = mledit_create(win, 0, 0, win->w, win->h / 2);
  widget_t* set_text = button_create(win, 0, 0, 0, 0);
  widget_t* open_with_anim = button_create(win, 0, 0, 0, 0);
  widget_t* open_without_anim = button_create(win, 0, 0, 0, 0);

  widget_set_name(mledit, "mledit");
  widget_set_text(mledit, L"multi line edit");
  mledit_set_focus(mledit, TRUE);

  widget_set_text(set_text, L"SetText");
  widget_set_self_layout_params(set_text, "10", "b:60", "25%", "30");
  widget_on(set_text, EVT_CLICK, on_click_set_text, mledit);

  widget_set_text(open_with_anim, L"Open");
  widget_set_self_layout_params(open_with_anim, "c", "b:60", "25%", "30");
  widget_on(open_with_anim, EVT_CLICK, on_click_open_window_with_anim, win);

  widget_set_text(open_without_anim, L"Open");
  widget_set_self_layout_params(open_without_anim, "r:10", "b:60", "25%", "30");
  widget_on(open_without_anim, EVT_CLICK, on_click_open_window_without_anim, win);

  widget_on(win, EVT_WINDOW_TO_BACKGROUND, on_window_to_background, win);
  widget_on(win, EVT_WINDOW_TO_FOREGROUND, on_window_to_foreground, win);

  widget_layout(win);
}

#include "demo_main.c"
