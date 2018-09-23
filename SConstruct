import os
import platform

OS_NAME=platform.system()
TK_C_ROOT = os.path.normpath(os.getcwd())
TK_C_3RD_ROOT = os.path.join(TK_C_ROOT, '3rd')
TK_C_BIN_DIR=os.path.join(TK_C_ROOT, 'bin')
TK_C_LIB_DIR=os.path.join(TK_C_ROOT, 'lib')

TK_ROOT = os.path.normpath(os.getcwd()+'/../awtk')
TK_SRC = os.path.join(TK_ROOT, 'src')
TK_3RD_ROOT = os.path.join(TK_ROOT, '3rd')
TK_TOOLS_ROOT = os.path.join(TK_ROOT, 'tools')
TK_BIN_DIR=os.path.join(TK_ROOT, 'bin')
TK_LIB_DIR=os.path.join(TK_ROOT, 'lib')

RES_ROOT = os.path.normpath(TK_ROOT + '/demos').replace("\\", "\\\\")

os.environ['TK_C_ROOT'] = TK_C_ROOT;
os.environ['BIN_DIR'] = TK_C_BIN_DIR;
os.environ['LIB_DIR'] = TK_C_LIB_DIR;

os.environ['TK_ROOT'] = TK_ROOT;
os.environ['TK_BIN_DIR'] = TK_BIN_DIR;
os.environ['TK_LIB_DIR'] = TK_LIB_DIR;

OS_LIBPATH=[]
OS_CPPPATH=[]
OS_FLAGS='-g -Wall'
OS_SUBSYSTEM_CONSOLE=''
OS_SUBSYSTEM_WINDOWS=''
OS_LINKFLAGS=''
OS_LIBS=['SDL2', 'glad', 'stdc++', 'pthread', 'm']

COMMON_CCFLAGS = ' -DHAS_STD_MALLOC -DHAS_STDIO -DRES_ROOT=\"\\\"'+RES_ROOT+'\\\"\" '

if OS_NAME == 'Darwin':
  OS_LINKFLAGS='-framework OpenGL'
  COMMON_CCFLAGS = COMMON_CCFLAGS + ' -D__APPLE__ -DHAS_PTHREAD -DMACOS'
  OS_LIBS = OS_LIBS + ['dl']
elif OS_NAME == 'Linux':
  OS_LIBS = ['GL'] + OS_LIBS + ['dl']
  COMMON_CCFLAGS = COMMON_CCFLAGS + ' -DLINUX -DHAS_PTHREAD'
elif OS_NAME == 'Windows':
  OS_LIBS=['SDL2', 'glad']
  OS_FLAGS='-DWIN32 -D_WIN32 -DWINDOWS /EHsc -D_CONSOLE  /DEBUG -DUNICODE -D_UNICODE /Od /ZI'
  OS_LINKFLAGS='/MACHINE:X64 /DEBUG'
  OS_LIBPATH=[TK_3RD_ROOT+'/SDL2-2.0.7/lib/x64']
  OS_CPPPATH=[TK_3RD_ROOT+'/SDL2-2.0.7/']
  OS_SUBSYSTEM_CONSOLE='/SUBSYSTEM:CONSOLE  '
  OS_SUBSYSTEM_WINDOWS='/SUBSYSTEM:WINDOWS  '

LIBS=['assets', 'awtk', 'gpinyin', 'awtk', 'linebreak', 'agge', 'nanovg'] + OS_LIBS

CCFLAGS=OS_FLAGS + COMMON_CCFLAGS 
CPPPATH=[TK_ROOT, 
  TK_SRC, 
  TK_3RD_ROOT, 
  TK_C_3RD_ROOT,
  os.path.join(TK_SRC, 'ext_widgets')]

LIBPATH = [TK_LIB_DIR, TK_C_LIB_DIR]

DefaultEnvironment(CCFLAGS = CCFLAGS, 
  CPPPATH = CPPPATH,
  LIBS=LIBS,
  LINKFLAGS=OS_LINKFLAGS,
  OS_SUBSYSTEM_CONSOLE=OS_SUBSYSTEM_CONSOLE,
  OS_SUBSYSTEM_WINDOWS=OS_SUBSYSTEM_WINDOWS,
  LIBPATH=LIBPATH + OS_LIBPATH)

SConscriptFiles= [
  'demos/SConscript'
  ]
  
SConscript(SConscriptFiles)

