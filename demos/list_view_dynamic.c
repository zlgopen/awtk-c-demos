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

typedef struct _item_info_t {
  const char* name;
  const char** details;
} item_info_t;

#include "list_view_data.inc"

#define WIDGET_PROP_USER_DATA "user_data"

static widget_t* application_create_list_item(widget_t* parent, uint32_t i, const char* text) {
  widget_t* item = list_item_create(parent, 0, 0, 0, 0);

  if (i % 2) {
    widget_use_style(item, "odd_clickable");
  } else {
    widget_use_style(item, "even_clickable");
  }
  widget_set_focusable(item, TRUE);
  widget_set_text_utf8(item, text);

  return item;
}

static ret_t quit_on_click(void* ctx, event_t* e) {
  tk_quit();
  return RET_OK;
}

static ret_t application_init_detail_list(widget_t* win, item_info_t* info) {
  uint32_t i = 0;
  const char* text = NULL;
  widget_t* item = NULL;
  widget_t* detail = widget_lookup(win, "detail", TRUE);

  widget_destroy_children(detail);
  for (i = 0; info->details[i] != NULL; i++) {
    text = info->details[i];
    item = application_create_list_item(detail, i, text);
  }

  return RET_OK;
}

static ret_t list_item_on_click(void* ctx, event_t* e) {
  item_info_t* info = (item_info_t*)ctx;
  widget_t* win = widget_get_window(WIDGET(e->target));

  application_init_detail_list(win, info);

  return RET_OK;
}

static ret_t application_init_overview_list(widget_t* win) {
  uint32_t i = 0;
  widget_t* item = NULL;
  widget_t* overview = widget_lookup(win, "overview", TRUE);

  for (i = 0; i < ARRAY_SIZE(all_items); i++) {
    const item_info_t* iter = all_items + i;

    item = application_create_list_item(overview, i, iter->name);
    widget_on(item, EVT_CLICK, list_item_on_click, (void*)iter);
  }

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_open("list_view_dynamic");

  application_init_overview_list(win);
  application_init_detail_list(win, all_items);
  widget_child_on(win, "close", EVT_CLICK, quit_on_click, NULL);

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");

  return RET_OK;
}

#define LCD_WIDTH 800
#define LCD_HEGHT 480
#include "awtk_main.inc"
