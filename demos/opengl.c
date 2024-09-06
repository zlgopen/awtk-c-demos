/**
 * File:   opengl.c
 * Author: AWTK Develop Team
 * Brief:  opengl demo
 *
 * Copyright (c) 2018 - 2024  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
 * 2024-09-06 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"

#if defined(WITH_GPU_GL)

#ifdef WITHOUT_GLAD
#include <SDL.h>
#define GL_GLEXT_PROTOTYPES 1
#ifdef IOS
#include <OpenGLES/gltypes.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#else
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>
#endif /*IOS*/
#define  opengl_init()
#else
#include "glad/glad.h"
#ifdef WIN32
#define opengl_init gladLoadGL
#else
#define  opengl_init()
#endif
#endif /*WITHOUT_GLAD*/

/*本示例中，OpenGL代码源于：https://learnopengl.com */

static const char* s_vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
static const char* s_fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

typedef struct _gl_info_t {
  uint32_t program;
  uint32_t triangle2_vao;
  uint32_t triangle1_vao;
} gl_info_t;

static uint32_t glhelper_create_program(const char* vertexShaderSource,
                                        const char* fragmentShaderSource) {
  int success;
  char infoLog[512];
  uint32_t shaderProgram = 0;
  uint32_t vertexShader = 0;
  uint32_t fragmentShader = 0;
  return_value_if_fail(vertexShaderSource != NULL && fragmentShaderSource != NULL, 0);

  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    log_warn("ERROR::SHADER::VERTEX::COMPILATION_FAILED: %s\n", infoLog);
  }

  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    log_warn("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: %s\n", infoLog);
  }

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    log_warn("ERROR::SHADER::PROGRAM::COMPILATION_FAILED: %s\n", infoLog);
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}

static uint32_t glhelper_create_vao(void* vertices, uint32_t size) {
  uint32_t VBO = 0, VAO = 0;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, size * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return VAO;
}

static ret_t glview_init(gl_info_t* info) {
  opengl_init();

  float triangle1_vertices[] = {
      -0.5f, -0.5f, 0.0f, 
      0.5f,  -0.5f, 0.0f,
      0.0f,  0.5f,  0.0f
  };

  float triangle2_vertices[] = {
      -0.5f, -1.0f, 0.0f, 
      0.5f,  -1.0f, 0.0f,
      0.0f,  -0.5f, 0.0f
  };

  info->program = glhelper_create_program(s_vertexShaderSource, s_fragmentShaderSource);
  info->triangle2_vao = glhelper_create_vao(triangle1_vertices, 3);
  info->triangle1_vao = glhelper_create_vao(triangle2_vertices, 3);

  return RET_OK;
}

static ret_t glview_render_triangle(gl_info_t* info, uint32_t VAO) {
  uint32_t shaderProgram = info->program;

  if (shaderProgram) {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(0);
    glBindVertexArray(0);
  }

  return RET_OK;
}

static ret_t glview_deinit(gl_info_t* info) {
  glDeleteProgram(info->program);

  memset(info, 0x00, sizeof(*info));

  return RET_OK;
}

static gl_info_t g_gl_info;

static ret_t on_close(void* ctx, event_t* e) {
  tk_quit();
  glview_deinit(&g_gl_info);

  return RET_OK;
}

static ret_t on_dialog(void* ctx, event_t* e) {
  dialog_info("Info", "It is a dialog.");
  return RET_OK;
}

static ret_t on_open(void* ctx, event_t* e) {
  window_open("basic");

  return RET_OK;
}

static ret_t on_paint(void* ctx, event_t* e) {
  gl_info_t* info = &g_gl_info;
  paint_event_t* evt = paint_event_cast(e);
  vgcanvas_t* vg = canvas_get_vgcanvas(evt->c);
  return_value_if_fail(vg != NULL, RET_BAD_PARAMS);

  vgcanvas_flush(vg);

  glview_render_triangle(info, info->triangle1_vao);
  glview_render_triangle(info, info->triangle2_vao);

  return RET_OK;
}
#endif/*WITH_GPU_GL*/

ret_t application_init() {
  widget_t* system_bar = window_open("system_bar");
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* close = button_create(win, 0, 0, 0, 0);
  widget_t* open = button_create(win, 0, 0, 0, 0);
  widget_t* dialog = button_create(win, 0, 0, 0, 0);

  (void)system_bar;
  widget_set_text_utf8(close, "Close");
  widget_set_self_layout_params(close, "c:-100", "b:10", "60", "30");
  
  widget_set_text_utf8(open, "Window");
  widget_set_self_layout_params(open, "c:100", "b:10", "60", "30");
  widget_on(open, EVT_CLICK, on_open, win);
  
  widget_set_text_utf8(dialog, "Dialog");
  widget_set_self_layout_params(dialog, "c", "b:10", "60", "30");
  widget_on(dialog, EVT_CLICK, on_dialog, win);

#if defined(WITH_GPU_GL)
  glview_init(&g_gl_info);
  widget_on(win, EVT_PAINT, on_paint, win);
  widget_on(close, EVT_CLICK, on_close, win);
#endif

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
