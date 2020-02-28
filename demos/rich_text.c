/**
 * File:   button.c
 * Author: AWTK Develop Team
 * Brief:  button demo
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
 * 2018-08-16 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* rich_text = rich_text_create(win, 0, 0, 0, 0);

  widget_set_text_utf8(
      rich_text,
      "<image name=\"bricks\"/><font color=\"gold\" align_v=\"bottom\" "
      "size=\"24\">hello awtk!</font><font color=\"green\" size=\"20\">ProTip! The "
      "feed shows you events from people you follow and repositories you watch. "
      "nhello world. </font><font color=\"red\" "
      "size=\"20\">确定取消中文字符测试。确定。取消。中文字符测试。</font>");

  widget_set_self_layout_params(rich_text, "center", "middle", "100%", "100%");
  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
