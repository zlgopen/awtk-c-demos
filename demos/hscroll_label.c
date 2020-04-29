/**
 * File:   hscroll_label.c
 * Author: AWTK Develop Team
 * Brief:  hscroll_label demo
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
 * 2020-04-29 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_close(void* ctx, event_t* e) {
  tk_quit();

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_open("hscroll_label");
  widget_t* h3 = widget_lookup(win, "h3", TRUE);
  const wchar_t* tips = L"我是中国人我爱中国，我是江西人我爱江西，我是深圳人我爱深圳。";

  widget_set_text(h3, tips);
  widget_child_on(win, "close", EVT_CLICK, on_close, win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
