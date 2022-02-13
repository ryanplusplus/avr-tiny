include tools/setup.mk

TARGET := attiny88
MCU := attiny88
FRAMEWORK := tiny
BUILD_DIR := ./build/$(TARGET)
DEVICE_PACK := Microchip.ATmega_DFP.2.3.126

# dwdebug or avrdude
UPLOAD_TYPE := dwdebug
AVRDUDE_PROGRAMMER_TYPE := atmelice_isp
AVRDUDE_PROGRAMMER_ARGS :=
DWDEBUG_DEVICE := ttyUSB0

DEFINES := \
  F_CPU=8000000UL \

# http://eleccelerator.com/fusecalc/fusecalc.php?chip=attiny88&LOW=EE&HIGH=9F&EXTENDED=FF&LOCKBIT=FF
FUSES := \
  lfuse=0xEE \
  hfuse=0x9F \
  efuse=0xFF \

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
