TARGET := atmega328p
MCU := atmega328p
FRAMEWORK := tiny

# dwdebug or avrdude
UPLOAD_TYPE := dwdebug
AVRDUDE_PROGRAMMER_TYPE := atmelice_isp
AVRDUDE_PROGRAMMER_ARGS :=
DWDEBUG_DEVICE := ttyUSB0

DEFINES := \
  F_CPU=8000000UL \

FUSES := \
  efuse=0xFD \
  hfuse=0x9E \
  lfuse=0xE2 \

BUILD_DIR := ./build/$(TARGET)

DEVICE_PACK := Atmel.ATmega_DFP.1.6.364

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

include lib_tiny.mk
include lib_tiny_cpp.mk

include tools/tools.mk
include docs.mk
