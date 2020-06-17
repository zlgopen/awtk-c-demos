/**
 * File:   label.c
 * Author: AWTK Develop Team
 * Brief:  label demo
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
 * 2018-08-15 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

/*
 * 如果非要在文件中使用中文，请务必保证当前源文件为：UTF-8 Unicode (with BOM)
 *
 * file demos/label_chinese.c
 * demos/label_chinese.c: C source, UTF-8 Unicode (with BOM) text, with CRLF line terminators
 */
ret_t application_init() {
  char str[256];
  char car_no_utf8[24];
  const wchar_t* car_no = L"粤B12345";
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* label = label_create(win, 10, 10, win->w - 20, win->h - 20);

  const char* type1 = "汽油";
  const char* type2 = "天然气";
  const char* type3 = "自动";

  tk_utf8_from_utf16(car_no, car_no_utf8, sizeof(car_no_utf8));
  tk_snprintf(str, sizeof(str),
              "当前状态:车牌%s；\n燃料[%s]；\n额定转速[%drpm]；\n调零[%s]；\n泄露[%s]", car_no_utf8,
              type1, 1024, type2, type3);

  widget_set_text_utf8(label, str);

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#define APP_DEFAULT_FONT "default_full"
#include "awtk_main.inc"
