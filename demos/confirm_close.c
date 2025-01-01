/**
 * File:   confirm_close.c
 * Author: AWTK Develop Team
 * Brief:  confirm close window
 *
 * Copyright (c) 2018 - 2025  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
 * 2021-10-18 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_request_close(void* ctx, event_t* e) {
  if(dialog_confirm("Confirm", "Are you sure to quit?") == RET_OK) {
    tk_quit();
  } 

  return RET_OK;
}

ret_t application_init() {
  window_open("system_bar"); 
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  widget_set_text_utf8(win, "confirm to close");
  widget_set_prop_str(win, WIDGET_PROP_CLOSABLE, "confirm");

  /*点击system bar关闭按钮或back按钮时触发该事件*/
  widget_on(win, EVT_REQUEST_CLOSE_WINDOW, on_request_close, NULL);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
