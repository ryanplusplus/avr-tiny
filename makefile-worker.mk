worker_path := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
tools_path := $(worker_path)tools/$(shell uname)
dwdebug_path := $(tools_path)/dwdebug
docs_mk_path := $(worker_path)docs.mk

SRCS := $(SRC_FILES)

ifneq ($(SRC_DIRS),)
SRCS += $(shell find $(SRC_DIRS) -maxdepth 1 -name *.c -or -name *.s -or -name *.S)
endif

LIB_SRCS := $(LIB_FILES)

ifneq ($(LIB_DIRS),)
LIB_SRCS += $(shell find $(LIB_DIRS) -maxdepth 1 -name *.c -or -name *.s -or -name *.S)
endif

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(SRCS:%=$(BUILD_DIR)/%.d)
LIB_OBJS := $(LIB_SRCS:%=$(BUILD_DIR)/%.o)
LIB_DEPS := $(LIB_SRCS:%=$(BUILD_DIR)/%.d)

INC_DIRS += $(shell find $(SRC_DIRS) -type d)
ifneq ($(LIB_DIRS),)
INC_DIRS += $(shell find $(LIB_DIRS) -type d)
endif

INC_FLAGS := $(addprefix -I,$(INC_DIRS))
DEFINE_FLAGS := $(addprefix -D,$(DEFINES))

CFLAGS += \
  $(INC_FLAGS) \
  $(DEFINE_FLAGS) \
  -Bpack/dev/$(MCU) \
  -fno-exceptions \
  -fdata-sections \
  -ffunction-sections \
  -nostdlib \
  -Wextra \
  -Werror \
  -Wfatal-errors \
  -Wno-implicit-fallthrough \

LDFLAGS += \
  $(CFLAGS) \
  --relax \

CC      := avr-gcc
AS      := avr-as
LD      := avr-gcc
AR      := avr-ar
OBJCOPY := avr-objcopy
SIZE    := avr-size

FUSES :=

ifneq ($(EFUSE),)
FUSES += -U efuse:w:$(EFUSE):m
endif

ifneq ($(HFUSE),)
FUSES += -U hfuse:w:$(HFUSE):m
endif

ifneq ($(LFUSE),)
FUSES += -U lfuse:w:$(LFUSE):m
endif

.PHONY: all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex
	@echo
	@$(SIZE) -C --mcu=$(MCU) $<

.PHONY: $(BUILD_DIR)/debug-server-avarice
$(BUILD_DIR)/debug-server-avarice:
	@echo "#!/bin/bash" > $@
	@echo "PORT=\`echo \"'\$$*'\" | sed 's/.*gdb_port \([^ ]*\).*/\\\1/'\`" >> $@
	@echo "avarice -g -w :\$$PORT" >> $@
	@chmod +x $@

.PHONY: $(BUILD_DIR)/debug-server-dwdebug
$(BUILD_DIR)/debug-server-dwdebug:
	@echo "#!/bin/bash" > $@
	@echo "$(dwdebug_path) verbose,gdbserver,device $(DWDEBUG_TOOL)" >> $@
	@chmod +x $@

.PHONY: debug-deps
debug-deps: $(BUILD_DIR)/debug-server-avarice $(BUILD_DIR)/debug-server-dwdebug $(BUILD_DIR)/$(TARGET).hex

ifeq ($(UPLOAD_TYPE),avrdude)
.PHONY: upload
upload: $(BUILD_DIR)/$(TARGET).hex
	@avrdude -c $(AVRDUDE_PROGRAMMER_TYPE) -p $(MCU) $(AVRDUDE_PROGRAMMER_ARGS) $(FUSES) -U flash:w:$<

.PHONY: erase
erase:
	@avrdude -c $(AVRDUDE_PROGRAMMER_TYPE) -p $(MCU) $(AVRDUDE_PROGRAMMER_ARGS) -e
endif

ifeq ($(UPLOAD_TYPE),dwdebug)
.PHONY: upload
upload: $(BUILD_DIR)/$(TARGET).elf
	@$(dwdebug_path) device $(DWDEBUG_TOOL),l $<,qr
endif

.PHONY: install_toolchain
install_toolchain:
	sudo apt-get install gcc-avr binutils-avr gdb-avr avr-libc avrdude avarice

$(BUILD_DIR)/$(TARGET).elf: $(OBJS) $(BUILD_DIR)/$(TARGET).lib
	@echo Linking $(notdir $@)...
	@mkdir -p $(dir $@)
	$(LD) $(OBJS) -Bpack/dev/$(MCU) -mmcu=$(MCU) -Wl,-Og -Wl,--gc-sections -Wl,--start-group $(BUILD_DIR)/$(TARGET).lib -Wl,--end-group -o $@ -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	@echo Creating $(notdir $@)...
	@mkdir -p $(dir $@)
	@$(OBJCOPY) -O ihex $< $@

$(BUILD_DIR)/$(TARGET).lib: $(LIB_OBJS)
	@echo Building $(notdir $@)...
	@mkdir -p $(dir $@)
	@$(AR) rcs $@ $^

$(BUILD_DIR)/%.s.o: %.s
	@echo Assembling $(notdir $@)...
	@mkdir -p $(dir $@)
	@$(AS) -g2 -mmcu=$(MCU) $< $(INC_FLAGS) -o $@

$(BUILD_DIR)/%.c.o: %.c
	@echo Compiling $(notdir $@)...
	@mkdir -p $(dir $@)
	@$(CC) -MM -MP -MF "$(@:%.o=%.d)" -MT "$(@)" $(CFLAGS) -E $<
	@$(CC) -x c -g -g2 -Os $(CFLAGS) -mmcu=$(MCU) -std=c99 -c $< -o $@

.PHONY: clean
clean:
	@echo Cleaning...
	@$(RM) -rf $(BUILD_DIR)

include $(docs_mk_path)

-include $(DEPS) $(LIB_DEPS)
