TARGET := tiny
BUILD_DIR := ./build

MCU := attiny85

DEVICE_PACK := Atmel.ATmega_DFP.1.6.364

# dwdebug or avrdude
UPLOAD_TYPE := dwdebug
AVRDUDE_PROGRAMMER_TYPE := atmelice_isp
AVRDUDE_PROGRAMMER_ARGS :=
DWDEBUG_DEVICE := ttyUSB0

ifeq ($(MCU),atmega328p)
DEFINES := \
  F_CPU=8000000UL \

FUSES := \
  efuse=0xFD \
  hfuse=0x9E \
  lfuse=0xE2 \

else ifeq ($(MCU),attiny85)
DEFINES := \
  F_CPU=8000000UL \

FUSES := \
  efuse=0xFF \
  hfuse=0x9C \
  lfuse=0xE2 \

else ifeq ($(MCU),atmega4808)
DEFINES := \
  F_CPU=20000000UL \

FUSES := \

endif

DEFINES += \

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
