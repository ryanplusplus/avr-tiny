TARGET := tiny
BUILD_DIR := ./build

MCU := attiny85

DEVICE_PACK := Atmel.ATmega_DFP.1.6.364

# dwdebug or avrdude
UPLOAD_TYPE := avrdude
AVRDUDE_PROGRAMMER_TYPE := usbtiny
AVRDUDE_PROGRAMMER_ARGS :=
DWDEBUG_TOOL := ttyUSB0

FUSES := \
  efuse=0xFF \
  hfuse=0x9C \
  lfuse=0xE2 \

DEFINES := \
  F_CPU=8000000UL \

include tools/defaults.mk

INC_DIRS := \

SYS_INC_DIRS := \

SRC_FILES := \

SRC_DIRS := \
  src \

include lib_tiny.mk

include tools/tools.mk
include docs.mk
