/**
 * File:   mutable_image.c
 * Author: AWTK Develop Team
 * Brief:  mutable image demo
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
 * 2019-02-28 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"
#include "blend/image_g2d.h"

typedef struct _decoding_info_t {
  bool_t quit;
  color_t color;
  bitmap_t* image;
  tk_mutex_t* mutex;
  tk_thread_t* thread;
} decoding_info_t;

static decoding_info_t* decoding_info_create(uint32_t w, uint32_t h, bitmap_format_t format) {
  decoding_info_t* decoding = TKMEM_ZALLOC(decoding_info_t);
  return_value_if_fail(decoding != NULL, NULL);

  decoding->mutex = tk_mutex_create();
  decoding->color = color_init(0, 0, 0, 0xff);
  decoding->image = bitmap_create_ex(w, h, 0, format);

  return decoding;
}

static ret_t decoding_info_destroy(decoding_info_t* decoding) {
  return_value_if_fail(decoding != NULL, RET_BAD_PARAMS);
  decoding->quit = TRUE;

  tk_thread_join(decoding->thread);
  bitmap_destroy(decoding->image);
  tk_mutex_destroy(decoding->mutex);
  TKMEM_FREE(decoding);

  log_debug("decoding_info_destroy\n");

  return RET_OK;
}

static color_t get_fill_color(decoding_info_t* decoding) {
  if (decoding->color.rgba.r < 0xff) {
    decoding->color.rgba.r++;
  } else if (decoding->color.rgba.g < 0xff) {
    decoding->color.rgba.g++;
  } else if (decoding->color.rgba.b < 0xff) {
    decoding->color.rgba.b++;
  } else {
    decoding->color.rgba.r = 0;
    decoding->color.rgba.g = 0;
    decoding->color.rgba.b = 0;
  }

  return decoding->color;
}

/*解码线程，模拟解码*/
static void* decoding_thread_entry(void* args) {
  decoding_info_t* decoding = (decoding_info_t*)args;
  bitmap_t* image = decoding->image;
  rect_t r = rect_init(0, 0, image->w, image->h);

  while (!(decoding->quit)) {
    tk_mutex_lock(decoding->mutex);
    image_fill(image, &r, get_fill_color(decoding));
    tk_mutex_unlock(decoding->mutex);

    sleep_ms(30);
  }

  return NULL;
}

static ret_t copy_decoded_image(void* ctx, bitmap_t* image) {
  rect_t r = rect_init(0, 0, image->w, image->h);
  decoding_info_t* decoding = (decoding_info_t*)ctx;

  tk_mutex_lock(decoding->mutex);
  image_copy(image, decoding->image, &r, 0, 0);
  tk_mutex_unlock(decoding->mutex);

  return RET_OK;
}

static decoding_info_t* s_decoding_info = NULL;

static ret_t click_to_quit(void* ctx, event_t* e) {
  tk_quit();
  return RET_OK;
}

ret_t application_init() {
  widget_t* ok = NULL;
  widget_t* image = NULL;
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  canvas_t* c = widget_get_canvas(win);

  /*XXX: 解码图片的格式和lcd的格式保持一致，才能获得最高的性能*/
  bitmap_format_t format = lcd_get_desired_bitmap_format(c->lcd);
  decoding_info_t* decoding = decoding_info_create(win->w, win->h, format);

  /*创建解码线程*/
  decoding->thread = tk_thread_create(decoding_thread_entry, decoding);

  image = mutable_image_create(win, 0, 0, win->w, win->h);
  mutable_image_set_prepare_image(image, copy_decoded_image, decoding);

  ok = button_create(win, 0, 0, 0, 0);
  widget_set_text(ok, L"quit");
  widget_on(ok, EVT_CLICK, click_to_quit, NULL);
  widget_set_self_layout_params(ok, "center", "button:60", "50%", "30");

  widget_layout(win);
  tk_thread_start(decoding->thread);
  window_manager_set_show_fps(win->parent, TRUE);

  s_decoding_info = decoding;

  return RET_OK;
}

ret_t application_exit() {
  decoding_info_destroy(s_decoding_info);
  return RET_OK;
}

#include "awtk_main.inc"
