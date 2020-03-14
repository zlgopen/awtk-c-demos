/**
 * File:   udp_settings.h
 * Author: AWTK Develop Team
 * Brief:  udp_settings
 *
 * Copyright (c) 2020 - 2020  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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

#ifndef TK_UDP_SETTINGS_H
#define TK_UDP_SETTINGS_H

#include "tkc/types_def.h"

BEGIN_C_DECLS

typedef struct _udp_settings_t {
  char host[TK_NAME_LEN + 1];
  int port;
} udp_settings_t;

ret_t udp_settings_open(udp_settings_t* udp);

END_C_DECLS

#endif /*TK_UDP_SETTINGS_H*/
