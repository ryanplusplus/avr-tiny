LIBS := tiny_cpp $(LIBS)

INC_DIRS += \
  lib/tiny_cpp/include \

SYS_INC_DIRS += \
  lib/cpp/include \

tiny_cpp_ASFLAGS := $(ASFLAGS)
tiny_cpp_CPPFLAGS := $(CPPFLAGS)
tiny_cpp_CFLAGS := $(CFLAGS)
tiny_cpp_CXXFLAGS := $(CXXFLAGS)

tiny_cpp_INC_DIRS := \
  lib/tiny_cpp/include \

tiny_cpp_SYS_INC_DIRS := \
  lib/cpp/include \

tiny_cpp_SRC_FILES := \

tiny_cpp_SRC_DIRS := \
  lib/tiny_cpp/src \
