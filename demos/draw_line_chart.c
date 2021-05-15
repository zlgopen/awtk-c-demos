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
#define MAX_VALUE 1000

typedef struct _line_chart_info_t {
  float max;
  float* data;
  uint32_t size;
  uint32_t capacity;

  color_t line_color;
  color_t axis_color;
  color_t text_color;
  color_t bg_color;
  uint32_t font_size;
  uint32_t title_font_size;
  const wchar_t* title;
} line_chart_info_t;

static line_chart_info_t* line_chart_info_create(uint32_t capacity, const wchar_t* title) {
  line_chart_info_t* info = TKMEM_ZALLOC(line_chart_info_t);
  return_value_if_fail(info != NULL, NULL);

  info->line_color = color_parse("black");
  info->bg_color = color_parse("#e0e0e0");
  info->axis_color = color_parse("red");
  info->text_color = color_parse("black");
  info->font_size = 18;
  info->title_font_size = 32;
  info->title = title;

  if (capacity > 0) {
    info->data = TKMEM_ALLOC(capacity * sizeof(info->data[0]));
    if (info->data != NULL) {
      info->capacity = capacity;
    }
  }

  return info;
}

static ret_t line_chart_info_destroy(line_chart_info_t* info) {
  return_value_if_fail(info != NULL, RET_FAIL);
  TKMEM_FREE(info->data);
  TKMEM_FREE(info);

  return RET_OK;
}

static ret_t line_chart_info_reset(line_chart_info_t* info) {
  return_value_if_fail(info != NULL, RET_FAIL);
  info->size = 0;
  info->max = 0;

  return RET_OK;
}

static ret_t line_chart_info_push(line_chart_info_t* info, float value) {
  return_value_if_fail(info != NULL && info->size < info->capacity, RET_FAIL);

  if (info->size == 0) {
    info->max = value;
  } else {
    if (value > info->max) {
      info->max = value;
    }
  }

  log_debug("%u %f %f\n", info->size, value, info->max);
  info->data[info->size++] = value;

  return RET_OK;
}

static ret_t on_paint_event(void* ctx, event_t* evt) {
  uint32_t i = 0;
  float x = 0;
  float y = 0;
  char str[32];
  float x_scale = 0;
  float y_scale = 0;
  wstr_t wstr;
  int32_t step = 0;
  int32_t left_margin = 60;
  int32_t right_margin = 10;
  int32_t top_margin = 30;
  int32_t bottom_margin = 30;
  widget_t* canvas_widget = WIDGET(evt->target);
  canvas_t* c = paint_event_cast(evt)->c;
  vgcanvas_t* vg = canvas_get_vgcanvas(c);
  line_chart_info_t* info = (line_chart_info_t*)ctx;
  float y_range = info->max;
  rect_t r = rect_init(canvas_widget->x, canvas_widget->y, canvas_widget->w, canvas_widget->h);

  wstr_init(&wstr, 100);

  /*绘制背景*/
  canvas_set_fill_color(c, info->bg_color);
  canvas_fill_rect(c, 0, 0, r.w, r.h);

  /*准备vgcanvas*/
  vgcanvas_save(vg);
  vgcanvas_clip_rect(vg, r.x, r.y, r.w, r.h);
  vgcanvas_translate(vg, r.x, r.y);

  /*绘制坐标轴*/
  vgcanvas_begin_path(vg);
  vgcanvas_move_to(vg, left_margin, top_margin);
  vgcanvas_line_to(vg, left_margin, r.h - bottom_margin);
  vgcanvas_line_to(vg, r.w - right_margin, r.h - bottom_margin);
  
  vgcanvas_set_stroke_color(vg, info->axis_color);
  vgcanvas_stroke(vg);

  /*将坐标原点移动到左下角*/
  vgcanvas_translate(vg, left_margin, r.h - bottom_margin);

  /*绘制数据线*/
  x_scale = (float)(r.w - left_margin - right_margin) / (float)(info->size);
  if (y_range > 0) {
    y_scale = (float)(r.h - top_margin - bottom_margin) / y_range;
  } else {
    y_scale = 1;
  }

  vgcanvas_begin_path(vg);
  for (i = 0; i < info->size; i++) {
    x = i * x_scale;
    y = -(info->max - info->data[i]) * y_scale;

    if (i == 0) {
      vgcanvas_move_to(vg, x, y);
    } else {
      vgcanvas_line_to(vg, x, y);
    }
  }
  vgcanvas_set_stroke_color(vg, info->line_color);
  vgcanvas_stroke(vg);

  vgcanvas_restore(vg);

  canvas_set_font(c, NULL, info->font_size);
  canvas_set_text_color(c, info->text_color);
  canvas_set_text_align(c, ALIGN_H_RIGHT, ALIGN_V_TOP);

  /*文字不能用vgcanvas绘制，否则嵌入式平台不支持*/

  /*绘制y坐标数值*/
#define NR 5
  x = 0;
  y = top_margin;
  step = (canvas_widget->h - top_margin - bottom_margin) / NR;

  for (i = 0; i <= NR; i++, y = y + step) {
    r = rect_init(x, y, left_margin-2, 20);
    uint32_t value = MAX_VALUE - i * MAX_VALUE / NR;
    tk_snprintf(str, sizeof(str), "%u", value);
    wstr_set_utf8(&wstr, str);

    canvas_draw_text_in_rect(c, wstr.str, wstr.size, &r);
  }

  /*绘制x坐标数值*/
  step = 50;
  x = left_margin + step;
  y = canvas_widget->h - bottom_margin;
  canvas_set_text_align(c, ALIGN_H_CENTER, ALIGN_V_TOP);

  for (i = 1; (x + step) < canvas_widget->w; i++, x = x + step) {
    uint32_t value = i * step;
    r = rect_init(x, y, step, 20);

    tk_snprintf(str, sizeof(str), "%u", value);
    wstr_set_utf8(&wstr, str);
    canvas_draw_text_in_rect(c, wstr.str, wstr.size, &r);
  }
 
  /*绘制标题*/
  canvas_set_font(c, NULL, info->title_font_size);
  r = rect_init(0, 0, canvas_widget->w, top_margin);
  canvas_draw_text_in_rect(c, info->title, wcslen(info->title), &r);

  wstr_reset(&wstr);

  return RET_OK;
}

static ret_t on_canvas_destroy(void* ctx, event_t* evt) {
  line_chart_info_t* info = (line_chart_info_t*)ctx;
  line_chart_info_destroy(info);

  return RET_REMOVE;
}

static ret_t line_chart_info_gen_data(line_chart_info_t* info, uint32_t nr) {
  line_chart_info_reset(info);

  while (nr > 0) {
    float value = random() % MAX_VALUE;
    line_chart_info_push(info, value);
    nr--;
  }

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = window_open("line_chart");
  widget_t* canvas = widget_lookup(win, "chart", TRUE);
  line_chart_info_t* info = line_chart_info_create(2048, L"Canvas demo");

  line_chart_info_gen_data(info, 500);

  widget_on(canvas, EVT_PAINT, on_paint_event, info);
  widget_on(canvas, EVT_DESTROY, on_canvas_destroy, info);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#undef LCD_WIDTH
#undef LCD_HEIGHT
#define LCD_WIDTH 1024
#define LCD_HEIGHT 720

#include "awtk_main.inc"
