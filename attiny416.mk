include tools/setup.mk

TARGET := attiny416
MCU := attiny416
FRAMEWORK := tiny
BUILD_DIR := ./build/$(TARGET)
DEVICE_PACK := Microchip.ATtiny_DFP.2.7.128

# dwdebug or avrdude
UPLOAD_TYPE := avrdude
AVRDUDE_PROGRAMMER_TYPE := xplainedmini_updi
AVRDUDE_PROGRAMMER_ARGS :=
DWDEBUG_DEVICE := ttyUSB0

DEFINES := \
  F_CPU=20000000UL \

FUSES := \

include tools/defaults.mk

CXXFLAGS += \
  -Wno-effc++ \

CPPFLAGS += \
  -flto \
  -fwhole-program \

SRC_DIRS := \
  src/hardware/common \
  src/hardware/$(MCU) \

SRC_FILES := \
  src/main.c \

include lib/tiny/lib_tiny.mk

.PHONY: all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex
	@$(SIZE) $<

include tools/tools.mk
