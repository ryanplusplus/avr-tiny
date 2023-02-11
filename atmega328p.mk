include tools/setup.mk

TARGET := atmega328p
MCU := atmega328p
FRAMEWORK ?= tiny
BUILD_DIR := ./build/$(TARGET)
DEVICE_PACK := Microchip.ATmega_DFP.3.0.158

# dwdebug or avrdude
UPLOAD_TYPE := dwdebug
AVRDUDE_PROGRAMMER_TYPE := atmelice_isp
AVRDUDE_PROGRAMMER_ARGS :=
DWDEBUG_DEVICE := ttyUSB0
BLOOM_DEBUG_TOOL := atmel-ice
BLOOM_DEBUG_INTERFACE := debug-wire
BLOOM_INSIGHT_ENABLED := false

DEFINES := \
  F_CPU=8000000UL \

# http://eleccelerator.com/fusecalc/fusecalc.php?chip=atmega328p&LOW=E2&HIGH=9E&EXTENDED=FF&LOCKBIT=FF
FUSES := \
  lfuse=0xE2 \
  hfuse=0x9E \
  efuse=0xFF \

include tools/defaults.mk

CXXFLAGS += \
  -Wno-effc++ \

CPPFLAGS += \
  -flto \
  -fwhole-program \

SRC_DIRS := \
  src/hardware/$(MCU) \
  src/hardware/common \

SRC_FILES := \
  src/main.c \

include lib/tiny/lib_tiny.mk

.PHONY: all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex
	@$(SIZE) $<

include tools/tools.mk
