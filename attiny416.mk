include tools/setup.mk

TARGET := attiny416
MCU := attiny416
FRAMEWORK := tiny
BUILD_DIR := ./build/$(TARGET)
DEVICE_PACK := Microchip.ATtiny_DFP.2.7.128

# dwdebug or avrdude
UPLOAD_TYPE := avrdude
AVRDUDE_PROGRAMMER_TYPE := xplainedmini_updi
AVRDUDE_PROGRAMMER_ARGS :=
DWDEBUG_DEVICE := ttyUSB0

DEFINES := \
  F_CPU=20000000UL \

FUSES := \

include tools/defaults.mk

CXXFLAGS += \
  -Wno-effc++ \

CPPFLAGS += \
  -flto \
  -fwhole-program \

SRC_DIRS := \
  src/hardware/common \
  src/hardware/$(MCU) \

ifeq ($(FRAMEWORK),tiny)
SRC_FILES := \
  src/main.c \

endif

ifeq ($(FRAMEWORK),tiny.cpp)
SRC_FILES := \
  src/main.cpp \

SRC_DIRS += \
  lib/cpp/src \

endif

include lib/tiny/lib_tiny.mk
include lib_tiny_cpp.mk

include tools/tools.mk
