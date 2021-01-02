/**
 * File:   canvas.c
 * Author: AWTK Develop Team
 * Brief:  canvas demo
 *
 * Copyright (c) 2019 - 2021  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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

#define MAX_POINTS 1024
static uint32_t s_points_nr;
static point_t s_points[MAX_POINTS];

static ret_t on_quit_click(void* ctx, event_t* evt) {
  tk_quit();
  return RET_OK;
}

static ret_t on_clear_click(void* ctx, event_t* evt) {
  s_points_nr = 0;
  widget_invalidate_force(WIDGET(ctx), NULL);

  return RET_OK;
}

static ret_t on_pointer_down(void* ctx, event_t* evt) {
  pointer_event_t* e = (pointer_event_t*)evt;
  point_t p = {e->x, e->y};

  s_points[s_points_nr++] = p;

  return RET_OK;
}

static ret_t on_pointer_move(void* ctx, event_t* evt) {
  pointer_event_t* e = (pointer_event_t*)evt;
  point_t p = {e->x, e->y};

  if (e->pressed) {
    if ((s_points_nr + 1) < MAX_POINTS) {
      s_points[s_points_nr++] = p;
    }
    log_debug("move %d: %d %d\n", s_points_nr, p.x, p.y);
  }

  widget_invalidate_force(WIDGET(ctx), NULL);

  return RET_OK;
}

static ret_t on_pointer_up(void* ctx, event_t* evt) {
  pointer_event_t* e = (pointer_event_t*)evt;
  point_t p = {e->x, e->y};

  if ((s_points_nr + 1) < MAX_POINTS) {
    s_points[s_points_nr++] = p;
  }

  return RET_OK;
}

static ret_t on_paint_event(void* ctx, event_t* evt) {
  uint32_t i = 0;
  float_t ascent = 0;
  float_t descent = 0;
  float_t line_height = 0;

  widget_t* canvas_widget = WIDGET(ctx);
  canvas_t* c = paint_event_cast(evt)->c;
  vgcanvas_t* vg = canvas_get_vgcanvas(c);
  color_t fg = color_init(0x00, 0xe0, 0xe0, 0xff);
  color_t tc = color_init(0, 0, 0, 0xff);

  rect_t r = rect_init(canvas_widget->x, canvas_widget->y, canvas_widget->w, canvas_widget->h);

  vgcanvas_save(vg);
  vgcanvas_clip_rect(vg, r.x, r.y, r.w, r.h);
  vgcanvas_translate(vg, r.x, r.y);

  vgcanvas_set_stroke_color(vg, fg);
  vgcanvas_set_line_width(vg, 3);

  for (i = 0; i < s_points_nr; i++) {
    point_t* p = s_points + i;
    if (i == 0) {
      vgcanvas_move_to(vg, p->x, p->y);
    } else {
      vgcanvas_line_to(vg, p->x, p->y);
    }
    log_debug("%u: %d %d\n", i, p->x, p->y);
  }

  vgcanvas_stroke(vg);

  if (s_points_nr < 2) {
    const wchar_t* tips = L"Drag mouse to draw line.";
    canvas_set_font(c, NULL, 20);
    canvas_set_text_color(c, tc);
    canvas_draw_text(c, tips, wcslen(tips), 20, r.h / 2);

    canvas_get_text_metrics(c, &ascent, &descent, &line_height);
    log_debug("text_metrics: %d %d %d\n", (int)ascent, (int)descent, (int)line_height);
  }

  vgcanvas_restore(vg);

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* canvas = canvas_widget_create(win, 10, 10, win->w - 20, win->h - 50);
  widget_t* clear = button_create(win, 10, win->h - 40, 60, 30);
  widget_t* quit = button_create(win, win->w - 70, win->h - 40, 60, 30);

  widget_on(canvas, EVT_PAINT, on_paint_event, canvas);
  widget_on(canvas, EVT_POINTER_DOWN, on_pointer_down, canvas);
  widget_on(canvas, EVT_POINTER_MOVE, on_pointer_move, canvas);
  widget_on(canvas, EVT_POINTER_UP, on_pointer_up, canvas);

  widget_set_text(quit, L"Quit");
  widget_set_text(clear, L"Clear");
  widget_on(clear, EVT_CLICK, on_clear_click, canvas);
  widget_on(quit, EVT_CLICK, on_quit_click, NULL);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
