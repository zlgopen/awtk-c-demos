/**
 * File:   udp_settings.c
 * Author: AWTK Develop Team
 * Brief:  udp_settings
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
 * 2020-03-14 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"
#include "udp_settings.h"

static ret_t on_click_cancel(void* ctx, event_t* e) {
  widget_t* dialog = WIDGET(ctx);
  dialog_quit(dialog, DIALOG_QUIT_CANCEL);

  return RET_OK;
}

static ret_t on_click_ok(void* ctx, event_t* e) {
  widget_t* dialog = WIDGET(ctx);
  dialog_quit(dialog, DIALOG_QUIT_OK);

  return RET_OK;
}

ret_t udp_settings_open(udp_settings_t* udp) {
  widget_t* dlg = dialog_create(NULL, 0, 0, 240, 150);

  widget_t* port_label = label_create(dlg, 0, 0, 0, 0);
  widget_t* port_edit = edit_create(dlg, 0, 0, 0, 0);
  widget_t* host_label = label_create(dlg, 0, 0, 0, 0);
  widget_t* host_edit = edit_create(dlg, 0, 0, 0, 0);
  widget_t* cancel_button = button_create(dlg, 0, 0, 0, 0);
  widget_t* ok_button = button_create(dlg, 0, 0, 0, 0);

  widget_use_style(dlg, "notitle");
  widget_set_text(port_label, L"Port:");
  widget_set_text(host_label, L"Host:");
  widget_set_text(ok_button, L"OK");
  widget_set_text(cancel_button, L"Cancel");
  edit_set_input_type(port_edit, INPUT_INT);
  edit_set_int_limit(port_edit, 1024, 60000, 1);

  widget_set_name(host_edit, "host");
  widget_set_name(port_edit, "port");

  widget_set_self_layout_params(port_label, "10", "10", "80", "30");
  widget_set_self_layout_params(port_edit, "100", "10", "80", "30");

  widget_set_self_layout_params(host_label, "10", "60", "80", "30");
  widget_set_self_layout_params(host_edit, "100", "60", "-110", "30");

  widget_set_self_layout_params(ok_button, "center:-60", "b:10", "80", "30");
  widget_set_self_layout_params(cancel_button, "center:60", "b:10", "80", "30");

  widget_on(cancel_button, EVT_CLICK, on_click_cancel, dlg);
  widget_on(ok_button, EVT_CLICK, on_click_ok, dlg);

  widget_layout(dlg);

  edit_set_int(port_edit, udp->port);
  widget_set_text_utf8(host_edit, udp->host);

  if (dialog_modal(dlg) == DIALOG_QUIT_OK) {
    const wchar_t* str = widget_get_text(host_edit);

    udp->port = edit_get_int(port_edit);
    tk_utf8_from_utf16(str, udp->host, TK_NAME_LEN);

    return RET_OK;
  }

  return RET_FAIL;
}
