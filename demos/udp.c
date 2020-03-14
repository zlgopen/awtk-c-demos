/**
 * File:   udp.c
 * Author: AWTK Develop Team
 * Brief:  udp
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
 * 2020-03-14 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"
#include "udp_settings.h"
#include "streams/inet/iostream_udp.h"

typedef struct _app_t {
  bool_t quited;
  tk_iostream_t* udp;
  tk_thread_t* thread;
  udp_settings_t settings;

  widget_t* win;
  widget_t* data_edit;
  widget_t* recv_label;
  widget_t* settings_label;
} app_t;

static app_t s_app;
static ret_t update_setings_label(void);

static ret_t idle_update_recv_data(const idle_info_t* info) {
  char* str = (char*)(info->ctx);

  widget_set_text_utf8(s_app.recv_label, str);
  TKMEM_FREE(str);

  return RET_REMOVE;
}

static void* read_thread(void* args) {
  int ret = 0;
  char buff[1024];
  tk_iostream_t* iostream = s_app.udp;
  tk_istream_t* istream = tk_iostream_get_istream(iostream);
  log_debug("read_thread started\n");

  while (!(s_app.quited)) {
    if (tk_istream_wait_for_data(istream, 30) == RET_OK) {
      ret = tk_istream_read(istream, (uint8_t*)buff, sizeof(buff));
      if (ret > 0) {
        buff[ret] = '\0';
        idle_add(idle_update_recv_data, tk_strdup(buff));
        log_debug("%d: %s\n", ret, buff);
      } else {
        log_debug("no data\n");
      }
    }
  }

  log_debug("read_thread quited\n");

  return NULL;
}

static ret_t on_click_close(void* ctx, event_t* e) {
  s_app.quited = TRUE;

  tk_quit();

  return RET_OK;
}

static ret_t on_click_send(void* ctx, event_t* e) {
  str_t str;
  int ret = 0;
  tk_ostream_t* ostream = tk_iostream_get_ostream(s_app.udp);

  str_init(&str, 1000);
  str_from_wstr(&str, widget_get_text(s_app.data_edit));

  ret = tk_ostream_write(ostream, (uint8_t*)(str.str), str.size);
  log_debug("send ret=%d %s\n", ret, str.str);
  str_reset(&str);

  return RET_OK;
}

static ret_t app_reset(void) {
  if (s_app.thread != NULL) {
    s_app.quited = TRUE;
    tk_thread_destroy(s_app.thread);
    s_app.thread = NULL;
  }

  if (s_app.udp != NULL) {
    OBJECT_UNREF(s_app.udp);
    s_app.udp = NULL;
  }

  return RET_OK;
}

static ret_t start_read_thread(void) {
  s_app.quited = FALSE;
  s_app.udp = tk_iostream_udp_create_client(s_app.settings.host, s_app.settings.port);
  s_app.thread = tk_thread_create(read_thread, NULL);
  tk_thread_start(s_app.thread);

  return RET_OK;
}

static ret_t on_click_settings(void* ctx, event_t* e) {
  if (udp_settings_open(&s_app.settings) == RET_OK) {
    app_reset();
    start_read_thread();
    update_setings_label();
  }

  return RET_OK;
}

static ret_t update_setings_label(void) {
  char info[128];
  tk_snprintf(info, sizeof(info), "%s:%d", s_app.settings.host, s_app.settings.port);
  widget_set_text_utf8(s_app.settings_label, info);
  log_debug("connect: %s\n", info);

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  widget_t* settings_label = label_create(win, 0, 0, 0, 0);
  widget_t* data_edit = edit_create(win, 0, 0, 0, 0);
  widget_t* close_button = button_create(win, 0, 0, 0, 0);
  widget_t* send_button = button_create(win, 0, 0, 0, 0);
  widget_t* settings_button = button_create(win, 0, 0, 0, 0);
  widget_t* recv_label = label_create(win, 0, 0, 0, 0);

  widget_set_text(data_edit, L"some data");
  widget_set_text(send_button, L"Send");
  widget_set_text(close_button, L"Close");
  widget_set_text(settings_button, L"Settings");
  widget_set_text(recv_label, L"no recv data");

  widget_set_self_layout_params(settings_label, "10", "10", "80%", "30");
  widget_set_self_layout_params(data_edit, "10", "50", "80%", "30");

  widget_set_self_layout_params(settings_button, "10", "middle", "80", "30");
  widget_set_self_layout_params(send_button, "center", "middle", "80", "30");
  widget_set_self_layout_params(close_button, "r:10", "middle", "80", "30");
  widget_set_self_layout_params(recv_label, "r:10", "middle:60", "80%", "100");

  widget_on(close_button, EVT_CLICK, on_click_close, NULL);
  widget_on(send_button, EVT_CLICK, on_click_send, NULL);
  widget_on(settings_button, EVT_CLICK, on_click_settings, NULL);

  widget_layout(win);

  socket_init();
  s_app.win = win;
  s_app.recv_label = recv_label;
  s_app.data_edit = data_edit;
  s_app.settings.port = 8000;
  s_app.settings_label = settings_label;

  strcpy(s_app.settings.host, "localhost");

  update_setings_label();
  start_read_thread();

  return RET_OK;
}

ret_t application_exit() {
  app_reset();
  socket_deinit();
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"

/*
 * 使用说明：
 * 
 * 本程序需要配合 AWTK 中的 udp_recv 使用。
 * 
 * 1.先启动 udp_recv:
 * 
 * cd awtk
 * ./bin/udp_recv 8000
 * 
 * 2.运行demo_udp，并将设置中的IP和端口指向udp_recv的IP和端口。
 * 
 * cd awtk-c-demos
 * ./bin/demo_udp
 * 
 * 3.点击demo_udp中的『Send』按钮，它会把编辑器中的数据发送给udp_recv。
 * 
 * 4.udp_recv收到数据再把数据原样返回给demo_udp。
 * 
 * 5.demo_udp再将数据显示到界面上。 
 * 
 */
