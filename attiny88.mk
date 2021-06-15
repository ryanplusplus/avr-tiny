TARGET := attiny88
MCU := attiny88
FRAMEWORK := tiny

# dwdebug or avrdude
UPLOAD_TYPE := avrdude
AVRDUDE_PROGRAMMER_TYPE := atmelice_isp
AVRDUDE_PROGRAMMER_ARGS :=
DWDEBUG_DEVICE := ttyUSB0

DEFINES := \
  F_CPU=8000000UL \

# http://eleccelerator.com/fusecalc/fusecalc.php?chip=attiny88&LOW=E2&HIGH=9C&EXTENDED=FF&LOCKBIT=FF
FUSES := \
  lfuse=0xEE \
  hfuse=0x9C \
  efuse=0xFF \

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
