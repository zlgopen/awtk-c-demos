/**
 * File:   basic.c
 * Author: AWTK Develop Team
 * Brief:  demo widget clone bench mark
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
 * 2019-11-108 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_click(void* ctx, event_t* e) {
  uint32_t i = 0;
  uint32_t n = 10000;
  widget_t* view = WIDGET(ctx);
  widget_t* item = widget_get_child(view, 0);
  uint64_t start = time_now_ms();
  uint64_t cost = time_now_ms();

  for (i = 0; i < n; i++) {
    widget_clone(item, view);
  }

  cost = time_now_ms() - start;
  log_debug("clone %u cost %llu\n", n, cost);

  return RET_OK;
}

static ret_t on_scroll_start(void* ctx, event_t* e) {
  scroll_view_t* view = SCROLL_VIEW(e->target);

  log_debug("scroll start: %d\n", view->yoffset);

  return RET_OK;
}

static ret_t on_scroll_end(void* ctx, event_t* e) {
  widget_t* widget = WIDGET(e->target);
  scroll_view_t* view = SCROLL_VIEW(widget);
  widget_t* item = widget_get_child(widget, 0);

  log_debug("scroll end: yoffset=%d virtual_h=%d h=%d\n", view->yoffset, view->virtual_h, widget->h);

  if((view->yoffset + widget->h) >= view->virtual_h) {
    int32_t i = 0;

    for(i = 0; i < 20; i++) {
      widget_clone(item, widget);
    }
  }

  return RET_OK;
}

static ret_t on_scroll(void* ctx, event_t* e) {
  scroll_view_t* view = SCROLL_VIEW(e->target);

  log_debug("scroll: %d\n", view->yoffset);

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_open("list_view_m");
  widget_t* view = widget_lookup_by_type(win, WIDGET_TYPE_SCROLL_VIEW, TRUE);
  widget_t* button = widget_lookup(win, "close", TRUE);

  widget_set_text_utf8(button, "Clone");
  widget_on(button, EVT_CLICK, on_click, view);
  widget_on(view, EVT_SCROLL_START, on_scroll_start, view);
  widget_on(view, EVT_SCROLL_END, on_scroll_end, view);
  widget_on(view, EVT_SCROLL, on_scroll, view);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
