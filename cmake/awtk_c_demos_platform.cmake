# Platform and app compile definitions (mirrors scripts/app_helper_base.py + awtk_config_common.py).

function(awtk_c_demos_apply_compile_defs _target)
  target_compile_definitions(${_target} PRIVATE
    LCD_WIDTH=800
    LCD_HEIGHT=480
    APP_DEFAULT_FONT="default"
    APP_THEME="default"
    APP_RES_ROOT="../res"
    APP_DEFAULT_LANGUAGE="zh"
    APP_DEFAULT_COUNTRY="CN"
    APP_ROOT="${CMAKE_SOURCE_DIR}"
  )

  if(APPLE)
    target_compile_definitions(${_target} PRIVATE __APPLE__ HAS_PTHREAD MACOS)
    target_compile_options(${_target} PRIVATE -DWITHOUT_GLAD=1)
  elseif(UNIX)
    target_compile_definitions(${_target} PRIVATE LINUX HAS_PTHREAD)
  elseif(WIN32)
    target_compile_definitions(${_target} PRIVATE WIN32 WINDOWS)
  endif()
endfunction()
