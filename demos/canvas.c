/**
 * File:   canvas.c
 * Author: AWTK Develop Team
 * Brief:  canvas demo
 *
 * Copyright (c) 2019 - 2019  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
 * 2019-01-09 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_paint_event(void* ctx, event_t* evt) {
  widget_t* canvas_widget = WIDGET(ctx);
  canvas_t* c = paint_event_cast(evt)->c;
  vgcanvas_t* vg = canvas_get_vgcanvas(c);
  color_t bg = color_init(0xe0, 0xe0, 0xe0, 0xff);
  color_t tc = color_init(0, 0, 0, 0xff);
  rect_t r = rect_init(canvas_widget->x, canvas_widget->y, canvas_widget->w, canvas_widget->h);

  vgcanvas_save(vg);
  vgcanvas_clip_rect(vg, r.x, r.y, r.w, r.h);
  vgcanvas_translate(vg, r.x, r.y);

  vgcanvas_set_fill_color(vg, bg);
  vgcanvas_rect(vg, 0, 0, r.w, r.h);
  vgcanvas_fill(vg);

  canvas_set_font(c, NULL, 20);
  canvas_set_text_color(c, tc);
  canvas_draw_text(c, L"Hello AWTK", 10, 20, r.h / 2);

  vgcanvas_restore(vg);

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* canvas = canvas_widget_create(win, 10, 10, win->w - 20, win->h - 20);

  widget_on(canvas, EVT_PAINT, on_paint_event, canvas);
  
  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"

