TARGET := tiny
BUILD_DIR := ./build

MCU := atmega4809

PACK := Atmel.ATmega_DFP.1.6.364

# dwdebug or avrdude
UPLOAD_TYPE := dwdebug
AVRDUDE_PROGRAMMER_TYPE := dragon_isp
AVRDUDE_PROGRAMMER_ARGS :=
DWDEBUG_TOOL := ttyUSB0

# This almost certainly doesn't work with megaavr 0-series
EFUSE := 0xFD
HFUSE := 0x9E
LFUSE := 0xE2

DEFINES := \
	F_CPU=3333333UL \

include tools/avr-gcc-tools/defaults.mk

SRC_FILES := \

SRC_DIRS := \
  src \

LIB_FILES := \

LIB_DIRS := \
  lib/tiny/src \

INC_DIRS := \
  lib/tiny/include \

include tools/avr-gcc-tools/tools.mk
