ASFLAGS := \
  -mmcu=$(MCU) \
  -g2 \

CPPFLAGS := \
  -mmcu=$(MCU) \
  -g \
  -g2 \
  -Os \
  -fdata-sections \
  -ffunction-sections \
  -Wall \
  -Wextra \
  -Werror \
  -Wfatal-errors \
  $(addprefix -D,$(DEFINES)) \

ifneq ($(PACK),)
CPPFLAGS += -Bdfp/$(PACK)/gcc/dev/$(MCU)
endif

CFLAGS := \
  -std=c99 \

CXXFLAGS := \
  -fno-rtti \
  -fno-exceptions \
  -fno-non-call-exceptions \
  -fno-use-cxa-atexit \
  -Weffc++ \
  -std=c++17 \

LDFLAGS := \
  -Og \
  --gc-sections \
  -Map=$(BUILD_DIR)/$(TARGET).map \
