/**
 * File:   tcp_client.c
 * Author: AWTK Develop Team
 * Brief:  button demo
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
 * 2021-08-23 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"
#include "tkc/socket_helper.h"
#include "tkc/event_source_fd.h"
#include "streams/inet/iostream_tcp.h"

#define STR_PROP_IOSTREAM "iostream"

static tk_iostream_t* tcp_client_connect(event_source_on_event_t on_data, void* ctx, const char* host, int port) {
  tk_iostream_t* iostream = NULL;
  event_source_t* source = NULL;
  int sock = tcp_connect(host, port);
  return_value_if_fail(sock >= 0, NULL);

  iostream = tk_iostream_tcp_create(sock);
  if (iostream != NULL) {
    source = event_source_fd_create(sock, on_data, ctx);
    if(source != NULL) {
      main_loop_add_event_source(main_loop(), source);
    }
  }
  
  if(source == NULL) {
    OBJECT_UNREF(iostream);
    socket_close(sock);
    return NULL;
  } else {
    return iostream;
  }
}

static ret_t tcp_client_on_data(event_source_t* source) {
  char buff[128];
  widget_t* win = WIDGET(EVENT_SOURCE_FD(source)->ctx); 
  widget_t* recv_message = widget_lookup(win, "recv_message", TRUE);
  tk_iostream_t* iostream = TK_IOSTREAM(widget_get_prop_pointer(win, STR_PROP_IOSTREAM));
  tk_istream_t* in = tk_iostream_get_istream(iostream);

  memset(buff, 0x00, sizeof(buff));
  tk_istream_read(in, buff, sizeof(buff));

  if (object_get_prop_bool(OBJECT(iostream), TK_STREAM_PROP_IS_OK, FALSE)) {
    widget_set_text_utf8(recv_message, buff);
    return RET_OK;
  } else {
    OBJECT_UNREF(iostream);
    widget_set_prop_pointer(win, STR_PROP_IOSTREAM, NULL);
    log_debug("connection broken\n");
    return RET_REMOVE;
  }
}


static ret_t on_connect(void* ctx, event_t* e) {
  char text[128];
  char host[128];
  int port = 0;
  widget_t* win = WIDGET(ctx);
  tk_iostream_t* iostream = NULL;
  widget_t* button = WIDGET(e->target);
  widget_t* host_port = widget_lookup(win, "host", TRUE);
  widget_get_text_utf8(host_port, text, sizeof(text));
 
  memset(host, 0x00, sizeof(host));
  tk_sscanf(text, "%[^:]:%d", host, &port);

  iostream = tcp_client_connect(tcp_client_on_data, win, host, port);
  return_value_if_fail(iostream != NULL, RET_OK);
  widget_set_prop_pointer(win, STR_PROP_IOSTREAM, OBJECT(iostream));

  widget_set_enable(button, FALSE);
  log_debug("on_click: %s\n", button->name);
  return RET_OK;
}

static ret_t on_send(void* ctx, event_t* e) {
  char text[128];
  widget_t* win = WIDGET(ctx);
  widget_t* message = widget_lookup(win, "message", TRUE);
  tk_iostream_t* iostream = TK_IOSTREAM(widget_get_prop_pointer(win, STR_PROP_IOSTREAM));
  tk_ostream_t* out = tk_iostream_get_ostream(iostream);
  return_value_if_fail(out != NULL, RET_OK);

  memset(text, 0x00, sizeof(text));
  widget_get_text_utf8(message, text, sizeof(text));
  tk_ostream_write(out, text, strlen(text));

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* host = edit_create(win, 0, 0, 0, 0);
  widget_t* connect = button_create(win, 0, 0, 0, 0);
  widget_t* message = edit_create(win, 0, 0, 0, 0);
  widget_t* send = button_create(win, 0, 0, 0, 0);
  widget_t* recv_message = label_create(win, 0, 0, 0, 0);
  
  widget_set_name(host, "host");
  widget_set_text_utf8(host, "localhost:8080");
  widget_set_self_layout_params(host, "center", "10", "80%", "30");
  
  widget_set_name(message, "message");
  widget_set_text_utf8(message, "hello");
  widget_set_self_layout_params(message, "center", "60", "80%", "30");
  
  widget_set_name(recv_message, "recv_message");
  widget_set_text_utf8(recv_message, "none");
  widget_set_self_layout_params(recv_message, "center", "110", "80%", "100");

  widget_set_text_utf8(connect, "connect");
  widget_set_self_layout_params(connect, "10", "middle:80", "40%", "30");
  widget_on(connect, EVT_CLICK, on_connect, win);
  
  widget_set_text_utf8(send, "send");
  widget_set_self_layout_params(send, "r:10", "middle:80", "40%", "30");
  widget_on(send, EVT_CLICK, on_send, win);


  widget_layout(win);

  log_debug("please start echo server first:\n");
  log_debug("socat -v tcp-l:8080,fork exec:'/bin/cat'\n");
  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
