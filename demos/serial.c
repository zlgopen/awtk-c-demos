/**
 * File:   serial.c
 * Author: AWTK Develop Team
 * Brief:  serial demo
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
 * 2022-07-08 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"
#include "serial_widget/serial_widget.h"

static ret_t on_send(void* ctx, event_t* e) {
  char text[128] = {0};
  widget_t* win = WIDGET(ctx);
  serial_widget_t* serial = SERIAL_WIDGET(widget_lookup(win, "serial", TRUE));
  widget_t* edit = widget_lookup(win, "send_msg", TRUE); 
  widget_get_text_utf8(edit, text, sizeof(text)-1);

  tk_ostream_write_len(serial->ostream, text, strlen(text), 3000);

  return RET_OK;
}

static ret_t on_open(void* ctx, event_t* e) {
  char text[128] = {0};
  widget_t* win = WIDGET(ctx);
  widget_t* serial = widget_lookup(win, "serial", TRUE);
  widget_t* edit = widget_lookup(win, "device", TRUE); 
  widget_get_text_utf8(edit, text, sizeof(text)-1);

  serial_widget_set_device(serial, text);

  return RET_OK;
}

static ret_t on_data(void* ctx, event_t* e) {
  char text[128] = {0};
  widget_t* win = WIDGET(ctx);
  serial_widget_t* serial = SERIAL_WIDGET(e->target);
  widget_t* label = widget_lookup(win, "recv_msg", TRUE);

  int32_t len = tk_istream_read(serial->istream, text, sizeof(text)-1);
  if(len > 0) {
    text[len] = '\0';
    widget_set_text_utf8(label, text);
  }

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_open("serial");

  widget_child_on(win, "send", EVT_CLICK, on_send, win);
  widget_child_on(win, "open", EVT_CLICK, on_open, win);
  widget_child_on(win, "serial", EVT_DATA, on_data, win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
