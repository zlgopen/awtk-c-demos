/**
 * File:   image_animation.c
 * Author: AWTK Develop Team
 * Brief:  image_animation demo
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
 * 2019-01-14 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

static ret_t on_click_fast(void* ctx, event_t* e) {
  widget_t* widget = WIDGET(ctx);
  image_animation_t* image_animation = IMAGE_ANIMATION(widget);
  int32_t interval = image_animation->interval - 10;
  if(interval < 16) {
    interval = 16;
  }

  image_animation_set_interval(widget, interval);

  log_debug("interval:%d\n", interval);

  return RET_OK;
}

static ret_t on_click_slow(void* ctx, event_t* e) {
  widget_t* widget = WIDGET(ctx);
  image_animation_t* image_animation = IMAGE_ANIMATION(widget);
  
  int32_t interval = image_animation->interval + 10;
  image_animation_set_interval(widget, interval);

  log_debug("interval:%d\n", interval);

  return RET_OK;
}

static ret_t on_click_start_pause(void* ctx, event_t* e) {
  widget_t* widget = WIDGET(ctx);
  image_animation_t* image_animation = IMAGE_ANIMATION(widget);

  if (image_animation_is_playing(widget)) {
    widget_set_prop_str(widget, WIDGET_PROP_EXEC, WIDGET_EXEC_PAUSE_ANIMATOR);
    widget_set_text_utf8(WIDGET(e->target), "play");
  } else {
    widget_set_prop_str(widget, WIDGET_PROP_EXEC, WIDGET_EXEC_START_ANIMATOR);
    widget_set_text_utf8(WIDGET(e->target), "puase");
  }

  log_debug("on_click_start_pause\n");
  return RET_OK;
}

ret_t application_init() {
  widget_t* image_animation = NULL;
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* fast = button_create(win, 0, 0, 0, 0);
  widget_t* slow = button_create(win, 0, 0, 0, 0);
  widget_t* start_pause = button_create(win, 0, 0, 0, 0);

  image_animation = image_animation_create(win, 10, 10, 200, 200);
  image_animation_set_image(image_animation, "ani");
  image_animation_set_interval(image_animation, 50);
  image_animation_set_range_sequence(image_animation, 1, 9);
  image_animation_play(image_animation);
  widget_set_self_layout_params(image_animation, "center", "10", "200", "200");
  
  widget_set_tr_text(fast, "fast");
  widget_set_self_layout_params(fast, "10", "b:10", "20%", "30");
  widget_on(fast, EVT_CLICK, on_click_fast, image_animation);
  
  widget_set_tr_text(slow, "slow");
  widget_set_self_layout_params(slow, "c", "b:10", "20%", "30");
  widget_on(slow, EVT_CLICK, on_click_slow, image_animation);
  
  widget_set_tr_text(start_pause, "pause");
  widget_set_self_layout_params(start_pause, "r:10", "b:10", "20%", "30");
  widget_on(start_pause, EVT_CLICK, on_click_start_pause, image_animation);

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
