TARGET := tiny
BUILD_DIR := ./build

MCU := atmega328p
PROGRAMMER_TYPE := dragon_isp
PROGRAMMER_ARGS :=
DWDEBUG_TOOL := ttyUSB0

EFUSE := 0xFD
HFUSE := 0x9E
LFUSE := 0xE2

DEFINES := \
  F_CPU=8000000UL \

SRC_FILES := \

SRC_DIRS := \
  src \

LIB_FILES := \

LIB_DIRS := \
  lib/tiny/src \

INC_DIRS := \
  lib/tiny/include \

include makefile-worker.mk
