TARGET := tiny
BUILD_DIR := ./build

MCU := atmega328p

DEVICE_PACK := Atmel.ATmega_DFP.1.6.364

# dwdebug or avrdude
UPLOAD_TYPE := dwdebug
AVRDUDE_PROGRAMMER_TYPE := dragon_isp
AVRDUDE_PROGRAMMER_ARGS :=
DWDEBUG_TOOL := ttyUSB0

FUSES := \
  efuse=0xFD \
  hfuse=0x9E \
  lfuse=0xE2 \

DEFINES := \
  F_CPU=8000000UL \

include tools/defaults.mk

INC_DIRS := \

SYS_INC_DIRS := \

SRC_FILES := \

SRC_DIRS := \
  src \
  src/hardware/$(MCU) \

include lib_tiny.mk

include tools/tools.mk
include docs.mk
