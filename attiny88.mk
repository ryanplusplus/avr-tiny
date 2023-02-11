include tools/setup.mk

TARGET := attiny88
MCU := attiny88
FRAMEWORK := tiny
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
  src/hardware/$(MCU) \
  src/hardware/common \

SRC_FILES := \
  src/main.c \

include lib/tiny/lib_tiny.mk

.PHONY: all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex
	@$(SIZE) $<

include tools/tools.mk
