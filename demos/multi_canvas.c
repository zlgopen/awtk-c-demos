/**
 * File:   multi_canvas.c
 * Author: AWTK Develop Team
 * Brief:  multi canvas demo
 *
 * Copyright (c) 2019 - 2025  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
 * 2022-01-13 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_paint_event(void* ctx, event_t* evt) {
  canvas_t* c = paint_event_cast(evt)->c;
  vgcanvas_t* vg = canvas_get_vgcanvas(c);
  widget_t* canvas_widget = WIDGET(evt->target);
  color_t fg = color_init(0x00, 0xe0, 0xe0, 0xff);
  const char* shape_type = (const char*)ctx;
  rect_t old_clip_rect = {0, 0, 0, 0}; 
  rect_t r = rect_init(canvas_widget->x, canvas_widget->y, canvas_widget->w, canvas_widget->h);


  vgcanvas_save(vg);
  canvas_get_clip_rect(c, &old_clip_rect);
  vgcanvas_clip_rect(vg, r.x, r.y, r.w, r.h);

  canvas_set_fill_color(c, fg);
  vgcanvas_set_fill_color(vg, fg);
  vgcanvas_translate(vg, r.x, r.y);
  vgcanvas_begin_path(vg);

  if(tk_str_eq(shape_type, "rect")) {
    canvas_fill_rect(c, 0, 0, r.w, r.h);
  }else if(tk_str_eq(shape_type, "circle")) {
    vgcanvas_arc(vg, r.w/2, r.h/2, tk_min(r.w, r.h)/2, 0, 2 * M_PI, FALSE);
    vgcanvas_fill(vg);
  }else if(tk_str_eq(shape_type, "diamond")) {
    vgcanvas_move_to(vg, 0, r.h/2); 
    vgcanvas_line_to(vg, r.w/2, 0);
    vgcanvas_line_to(vg, r.w, r.h/2);
    vgcanvas_line_to(vg, r.w/2, r.h);
    vgcanvas_close_path(vg);
    vgcanvas_fill(vg);
  }else if(tk_str_eq(shape_type, "triangle")) {
    vgcanvas_move_to(vg, 0, r.h); 
    vgcanvas_line_to(vg, r.w/2, 0);
    vgcanvas_line_to(vg, r.w, r.h);
    vgcanvas_close_path(vg);
    vgcanvas_fill(vg);
  }

  vgcanvas_clip_rect(vg, old_clip_rect.x, old_clip_rect.y, old_clip_rect.w, old_clip_rect.h);
  vgcanvas_restore(vg);

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* rect_widget = canvas_widget_create(win, 0, 0, 0, 0);
  widget_t* circle_widget = canvas_widget_create(win, 0, 0, 0, 0);
  widget_t* diamond_widget = canvas_widget_create(win, 0, 0, 0, 0);
  widget_t* triangle_widget = canvas_widget_create(win, 0, 0, 0, 0);
  widget_on(rect_widget, EVT_PAINT, on_paint_event, "rect");
  widget_on(circle_widget, EVT_PAINT, on_paint_event, "circle");
  widget_on(diamond_widget, EVT_PAINT, on_paint_event, "diamond");
  widget_on(triangle_widget, EVT_PAINT, on_paint_event, "triangle");
  
  widget_set_children_layout(win, "default(r=2,c=2,s=10,m=10)");
  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
