/**
 * File:   conf_json.c
 * Author: AWTK Develop Team
 * Brief:  conf_json demo
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
 * 2022-06-22 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"
#include "conf_io/conf_json.h"

ret_t application_init() {
  tk_object_t* doc = conf_json_load("./test.json", TRUE);
  tk_object_set_prop_str(doc, "name", "awtk");
  tk_object_set_prop_int(doc, "age", 100);
  conf_json_save_as(doc, "./test.json");
  TK_OBJECT_UNREF(doc);
  
  doc = conf_json_load("./test.json", TRUE);

  log_debug("name:%s\n", tk_object_get_prop_str(doc, "name"));
  log_debug("age:%d\n", tk_object_get_prop_int(doc, "age", 0));
  TK_OBJECT_UNREF(doc);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
