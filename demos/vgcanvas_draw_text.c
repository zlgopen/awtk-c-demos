/**
 * File:   vgcanvas_draw_text.c
 * Author: AWTK Develop Team
 * Brief:  vgcanvas_draw_text
 *
 * Copyright (c) 2020 - 2020  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
 * 2020-06-06 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

typedef struct _canvas_info_t {
  float rotation;
  float scale;
  float delta;
  bitmap_t* text_img;
} canvas_info_t;

static bitmap_t* bitmap_from_str(canvas_t* canvas, wchar_t* str, color_t tc);

static canvas_info_t* canvas_info_create(void) {
  return TKMEM_ZALLOC(canvas_info_t);
}

static ret_t canvas_info_destroy(canvas_info_t* info) {
  return RET_OK;
}

static ret_t canvas_info_ensure_text_image(canvas_info_t* info, canvas_t* canvas, wchar_t* str,
                                           color_t tc) {
  return_value_if_fail(info != NULL && canvas != NULL && str != NULL, RET_BAD_PARAMS);

  if (info->text_img != NULL) {
    return RET_OK;
  }

  info->text_img = bitmap_from_str(canvas, str, tc);

  return RET_OK;
}

static bitmap_t* bitmap_from_str(canvas_t* canvas, wchar_t* str, color_t tc) {
  glyph_t g;
  uint32_t x = 0;
  uint32_t y = 0;
  uint32_t i = 0;
  uint32_t w = 0;
  uint32_t h = 0;
  uint32_t ox = 0;
  font_vmetrics_t vm;
  uint32_t* p = NULL;
  uint32_t baseline = 0;
  bitmap_t* bitmap = NULL;
  uint32_t font_size = canvas->font_size;
  font_manager_t* fm = canvas->font_manager;
  font_t* font = font_manager_get_font(fm, canvas->font_name, font_size);
  return_value_if_fail(font != NULL, NULL);

  vm = font_get_vmetrics(font, font_size);
  h = vm.ascent - vm.descent;
  return_value_if_fail(h > 0, NULL);

  baseline = vm.ascent;
  for (i = 0; str[i]; i++) {
    return_value_if_fail(font_get_glyph(font, str[i], font_size, &g) == RET_OK, NULL);
    w += g.advance + 1;
  }

  bitmap = bitmap_create_ex(w, h, 0, BITMAP_FMT_RGBA8888);
  return_value_if_fail(bitmap != NULL, NULL);

  p = (uint32_t*)bitmap_lock_buffer_for_write(bitmap);

  memset(p, 0x00, w * h * 4);

  for (i = 0; str[i]; i++) {
    return_value_if_fail(font_get_glyph(font, str[i], font_size, &g) == RET_OK, NULL);

    for (y = 0; y < g.h; y++) {
      for (x = 0; x < g.w; x++) {
        int32_t dx = ox + g.x + x;
        int32_t dy = baseline + g.y + y;

        uint32_t* d = p +  dy * w + dx;
        const uint8_t* s = g.data + y * g.w + x;

        tc.rgba.a = *s;
        *d = tc.color;
      }
    }
    ox += g.advance + 1;
  }
  bitmap_unlock_buffer(bitmap);
  bitmap->flags |= BITMAP_FLAG_CHANGED;

  return bitmap;
}

static ret_t on_quit_click(void* ctx, event_t* evt) {
  tk_quit();

  return RET_OK;
}

static ret_t canvas_widget_draw_image_center(widget_t* widget, vgcanvas_t* vg, bitmap_t* img) {
  int32_t x = (widget->w - img->w) / 2;
  int32_t y = (widget->h - img->h) / 2;

  vgcanvas_draw_image(vg, img, 0, 0, img->w, img->h, x, y, img->w, img->h);

  return RET_OK;
}

static ret_t update_on_timer(const timer_info_t* info) {
  widget_invalidate(WIDGET(info->ctx), NULL);

  return RET_REPEAT;
}

static ret_t canvas_on_paint_event(void* ctx, event_t* evt) {
  bitmap_t img;
  int32_t cx = 10;
  int32_t cy = 10;
  widget_t* widget = WIDGET(evt->target);
  canvas_t* c = paint_event_cast(evt)->c;
  vgcanvas_t* vg = canvas_get_vgcanvas(c);
  canvas_info_t* info = (canvas_info_t*)(ctx);

  color_t tc = color_init(0, 0, 0, 0xff);

  canvas_set_font(c, NULL, 48);
  image_manager_get_bitmap(image_manager(), "1", &img);

  cx = widget->w / 2;
  cy = widget->h / 2;

  return_value_if_fail(canvas_info_ensure_text_image(info, c, widget->text.str, tc) == RET_OK,
                       RET_FAIL);

  vgcanvas_save(vg);
  vgcanvas_translate(vg, c->ox, c->oy);

  vgcanvas_translate(vg, cx, cy);
  vgcanvas_rotate(vg, info->rotation);
  vgcanvas_scale(vg, info->scale, info->scale);
  vgcanvas_translate(vg, -cx, -cy);

  canvas_widget_draw_image_center(widget, vg, &img);
  canvas_widget_draw_image_center(widget, vg, info->text_img);

  vgcanvas_restore(vg);

  if (info->scale > 1.2) {
    info->delta = -0.02;
  }

  if (info->scale < 0.1) {
    info->delta = 0.02;
  }

  info->rotation += 0.01;
  info->scale += info->delta;

  return RET_OK;
}

static ret_t canvas_on_detroy(void* ctx, event_t* e) {
  canvas_info_destroy((canvas_info_t*)ctx);

  return RET_OK;
}

ret_t application_init() {
  canvas_info_t* canvas_info = canvas_info_create();

  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* canvas = canvas_widget_create(win, 0, 0, 0, 0);
  widget_t* quit = button_create(win, win->w - 70, win->h - 40, 60, 30);

  widget_set_self_layout_params(canvas, "center", "middle", "240", "240");

  widget_set_text(canvas, L"AWTK");
  widget_on(canvas, EVT_PAINT, canvas_on_paint_event, canvas_info);
  widget_on(canvas, EVT_DESTROY, canvas_on_detroy, canvas_info);
  widget_add_timer(canvas, update_on_timer, 20);

  widget_set_text(quit, L"Quit");
  widget_on(quit, EVT_CLICK, on_quit_click, NULL);

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
