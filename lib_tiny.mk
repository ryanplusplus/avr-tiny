LIBS := tiny $(LIBS)

INC_DIRS += \
  lib/tiny/include \

tiny_LIB_ROOT := lib/tiny

tiny_ASFLAGS := $(ASFLAGS)
tiny_CPPFLAGS := $(CPPFLAGS)
tiny_CFLAGS := $(CFLAGS)
tiny_CXXFLAGS := $(CXXFLAGS)

tiny_CPPFLAGS += \
  -Wno-implicit-fallthrough \

tiny_INC_DIRS := \
  lib/tiny/include \

tiny_SYS_INC_DIRS := \

tiny_SRC_FILES := \

tiny_SRC_DIRS := \
  lib/tiny/src \
