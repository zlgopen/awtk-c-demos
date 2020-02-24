#include "awtk.h"

static ret_t on_view_paint(void* ctx, event_t* e) {
  log_debug("on_view_paint...\r\n");
  return RET_OK;
}

static ret_t on_cont_paint(void* ctx, event_t* e) {
  log_debug("on_cont_paint...\r\n");
  return RET_OK;
}

ret_t application_init() {
  widget_t* par_main = window_create(NULL, 0, 0, 0, 0);
  widget_set_style_str(par_main, "bg_color", "black");

  widget_t* edit = mledit_create(par_main, 10, 60, 230, 50);
  mledit_set_focus(edit, TRUE);  //

  widget_t* view = view_create(par_main, 2, 2, 80, 40);
  widget_set_style_str(view, "bg_color", "white");

  widget_t* cont_obj = canvas_widget_create(par_main, 90, 2, 80, 40);
  widget_set_style_str(cont_obj, "bg_color", "blue");

  widget_on(cont_obj, EVT_PAINT, on_cont_paint, NULL);
  widget_on(view, EVT_PAINT, on_view_paint, NULL);
  // widget_on(edit, EVT_VALUE_CHANGING, on_edit_changing, edit);
  
  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
