TARGET := tiny
BUILD_DIR := ./build

MCU := atmega328p
PROGRAMMER_TYPE := usbtiny
PROGRAMMER_ARGS :=

DEFINES := \
  F_CPU=1000000UL \

SRC_FILES := \

SRC_DIRS := \
  src \

LIB_FILES := \

LIB_DIRS := \
  lib/tiny/src \

INC_DIRS := \
  lib/tiny/include \

include makefile-worker.mk
