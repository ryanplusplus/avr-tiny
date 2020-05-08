TARGET := tiny
BUILD_DIR := ./build

MCU := atmega328p
PROGRAMMER_TYPE := dragon_isp
PROGRAMMER_ARGS :=

EFUSE := 0xFD
HFUSE := 0xD6
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
