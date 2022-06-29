/**
 * File:   tcp_server.c
 * Author: AWTK Develop Team
 * Brief:  tcp server demo
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
 * 2022-06-29 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"
#include "tkc/socket_helper.h"
#include "tkc/event_source_fd.h"
#include "streams/inet/iostream_tcp.h"

#define SERVER_PORT 9988

typedef ret_t (*tcp_server_on_client_data_t)(void* ctx, tk_iostream_t* client);

typedef struct _tcp_server_t {
  /*private*/
  int port;
  int sock;
  darray_t clients;
  uint32_t max_clients_nr;
  void* ctx;
  tcp_server_on_client_data_t on_client_data;
} tcp_server_t;

ret_t tcp_server_on_client_data(event_source_t* source) {
  uint32_t i = 0;
  int fd = event_source_get_fd(source);
  tcp_server_t* server = (tcp_server_t*)EVENT_SOURCE_FD(source)->ctx;

  for (i = 0; i < server->clients.size; i++) {
    tk_iostream_t* client = (tk_iostream_t*)darray_get(&(server->clients), i);
    if (fd == TK_IOSTREAM_TCP(client)->sock) {
      if (server->on_client_data(server->ctx, client) != RET_OK) {
        darray_remove(&(server->clients), client);
        log_debug("connect closed(%u)\n", server->clients.size);
        return RET_REMOVE;
      }
      break;
    }
  }

  return RET_OK;
}

ret_t tcp_server_on_client(event_source_t* source) {
  tk_iostream_t* client = NULL;
  event_source_t* client_source = NULL;
  int fd = event_source_get_fd(source);
  int sock = tk_tcp_accept(fd);
  tcp_server_t* server = (tcp_server_t*)EVENT_SOURCE_FD(source)->ctx;
  return_value_if_fail(sock >= 0, RET_REMOVE);

  client = tk_iostream_tcp_create(sock);
  goto_error_if_fail(client != NULL);
  client_source = event_source_fd_create(sock, tcp_server_on_client_data, server);
  goto_error_if_fail(client_source != NULL);
  goto_error_if_fail(main_loop_add_event_source(main_loop(), client_source) == RET_OK);
  goto_error_if_fail(darray_push(&(server->clients), client) == RET_OK);

  log_debug("client connected\n");

  return RET_OK;
error:
  tk_socket_close(sock);
  TK_OBJECT_UNREF(client);
  TK_OBJECT_UNREF(client_source);

  return RET_REMOVE;
}

ret_t tcp_server_destroy(tcp_server_t* server) {
  return_value_if_fail(server != NULL, RET_BAD_PARAMS);
  tk_socket_close(server->sock);
  darray_deinit(&(server->clients));
  TKMEM_FREE(server);

  return RET_OK;
}

tcp_server_t* tcp_server_create(int port, uint32_t max_clients_nr,
                                tcp_server_on_client_data_t on_data, void* ctx) {
  event_source_t* source = NULL;
  tcp_server_t* server = NULL;
  return_value_if_fail(on_data != NULL, NULL);
  return_value_if_fail(port > 0 && max_clients_nr > 0, NULL);
  server = TKMEM_ZALLOC(tcp_server_t);
  return_value_if_fail(server != NULL, NULL);

  server->port = port;
  server->on_client_data = on_data;
  server->max_clients_nr = max_clients_nr;
  server->sock = tk_tcp_listen(SERVER_PORT);

  goto_error_if_fail(server->sock >= 0);
  goto_error_if_fail(darray_init(&(server->clients), max_clients_nr, (tk_destroy_t)tk_object_unref, NULL) != NULL);
  source = event_source_fd_create(server->sock, tcp_server_on_client, server);
  goto_error_if_fail(source != NULL);
  goto_error_if_fail(main_loop_add_event_source(main_loop(), source) == RET_OK);
  
  log_debug("listen at %d\n", port);

  return server;
error:
  tcp_server_destroy(server);

  return NULL;
}

/************************************/

static ret_t application_on_client_data(void* ctx, tk_iostream_t* client) {
  char buff[256] = {0};
  tk_istream_t* in = tk_iostream_get_istream(client);
  tk_ostream_t* out = tk_iostream_get_ostream(client);
  int n = tk_istream_read(in, buff, sizeof(buff) - 1);

  if (n > 0) {
    buff[n] = '\0';
    /*echo back*/
    tk_ostream_write(out, buff, n);
    return RET_OK;
  } else {
    return RET_REMOVE;
  }
}

static tcp_server_t* s_server = NULL;
ret_t application_init(void) {
  s_server = tcp_server_create(SERVER_PORT, 3, application_on_client_data, NULL);
  return RET_OK;
}

ret_t application_exit(void) {
  log_debug("application_exit\n");
  tcp_server_destroy(s_server);
  return RET_OK;
}
#include "awtk_main.inc"
