/**
 * File:   button.c
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
 * 2018-08-16 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_timer(const timer_info_t* info) {
  widget_t* win = WIDGET(info->ctx);
  widget_invalidate(win, NULL);

  return RET_REPEAT;
}

static ret_t on_paint(void* ctx, event_t* e) {
  char text[32];
  bitmap_t img;
  widget_t* win = WIDGET(e->target);
  canvas_t* c = paint_event_cast(e)->c;
  vgcanvas_t* vg = canvas_get_vgcanvas(c);
  int32_t w = win->w;
  int32_t h = win->h;
  color_t bg_color = color_init(0xe0, 0xe0, 0xe0, 0xff);
  color_t line_color = color_init(0x00, 0xe0, 0x00, 0xff);
  color_t text_color = color_init(0x00, 0xe0, 0x00, 0xff);

  tk_snprintf(text, sizeof(text), "time:%u", (uint32_t)time_now_s());

  /*优先使用canvas绘制，在没有GPU的情况下，canvas比vgcanvas快10倍*/

  canvas_set_fill_color(c, bg_color);
  canvas_fill_rect(c, 0, 0, w, h);

  canvas_set_font(c, NULL, 20);
  canvas_set_text_color(c, text_color);
  canvas_draw_utf8(c, text, 20, 20);

  if (widget_load_image(win, "earth", &img) == RET_OK) {
    canvas_draw_icon(c, &img, w/2, h/2);
  }

  canvas_set_stroke_color(c, line_color);
  canvas_draw_hline(c, 0, h/2, w);
  canvas_draw_vline(c, w/2, 0, h);

  /*使用vg时一定放在save/restore之间*/
  vgcanvas_save(vg);

  vgcanvas_begin_path(vg);

  vgcanvas_translate(vg, w/2, h/2);
  vgcanvas_rotate(vg, M_PI/4);
  vgcanvas_move_to(vg, 0, 0);
  vgcanvas_line_to(vg, 100, 0);
  
  vgcanvas_set_line_width(vg, 5);
  vgcanvas_stroke(vg);

  vgcanvas_restore(vg);

  log_debug("EVT_PAINT\n");
  return RET_OK;
}

static ret_t on_debug(void* ctx, event_t* e) {
  log_debug("event:%s\n", (const char*)ctx);
  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);

  widget_on(win, EVT_PAINT, on_paint, NULL);
  widget_add_timer(win, on_timer, 1000);
  
  widget_on(win, EVT_BEFORE_PAINT, on_debug, "EVT_BEFORE_PAINT");
  widget_on(win, EVT_AFTER_PAINT, on_debug, "EVT_AFTER_PAINT");
  widget_on(win, EVT_PAINT_DONE, on_debug, "EVT_PAINT_DONE");

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
