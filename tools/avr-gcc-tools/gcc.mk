
BUILD_DEPS := $(BUILD_DEPS) $(MAKEFILE_LIST)

SRCS := $(SRC_FILES)

ifneq ($(SRC_DIRS),)
SRCS += $(shell find $(SRC_DIRS) -maxdepth 1 -name *.c -or -name *.s -or -name *.S)
endif

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(SRCS:%=$(BUILD_DIR)/%.d)

INC_DIRS += $(SRC_DIRS)
INC_FLAGS := $(addprefix -iquote,$(INC_DIRS))

SYS_INC_FLAGS := $(addprefix -I,$(SYS_INC_DIRS))

CPPFLAGS := \
  $(INC_FLAGS) \
  $(SYS_INC_FLAGS) \
  $(CPPFLAGS) \

COMMA :=,
LDFLAGS := \
  $(addprefix -Wl$(COMMA),$(LDFLAGS)) \

LDLIBS := \
	$(foreach _lib,$(LIBS),$(BUILD_DIR)/$(_lib).lib) \
	$(LDLIBS) \

TOOLCHAIN_PREFIX ?= arm-none-eabi-

CC      := $(TOOLCHAIN_PREFIX)gcc
CXX     := $(TOOLCHAIN_PREFIX)g++
AS      := $(TOOLCHAIN_PREFIX)as
LD      := $(TOOLCHAIN_PREFIX)gcc
AR      := $(TOOLCHAIN_PREFIX)ar
GDB     := $(TOOLCHAIN_PREFIX)gdb
OBJCOPY := $(TOOLCHAIN_PREFIX)objcopy
SIZE    := $(TOOLCHAIN_PREFIX)size

# $1 prefix
# $2 ASFLAGS
# $3 CPPFLAGS
# $4 CFLAGS
# $5 CXXFLAGS
define generate_compilation_rules

$$(BUILD_DIR)/$(1)%.s.o: $(1)%.s $$(BUILD_DEPS)
	@echo Assembling $$(notdir $$@)...
	@mkdir -p $$(dir $$@)
	@$$(AS) $(2) $$< -o $$@

$$(BUILD_DIR)/$(1)%.S.o: $(1)%.S $$(BUILD_DEPS)
	@echo Assembling $$(notdir $$@)...
	@mkdir -p $$(dir $$@)
	@$$(CC) -c $(2) $$< $(3) -o $$@

$$(BUILD_DIR)/$(1)%.c.o: $(1)%.c $$(BUILD_DEPS)
	@echo Compiling $$(notdir $$@)...
	@mkdir -p $$(dir $$@)
	@$$(CC) -MM -MP -MF "$$(@:%.o=%.d)" -MT "$$@" $(3) $(4) -E $$<
	@$$(CC) -x c $(3) $(4) -c $$< -o $$@

$$(BUILD_DIR)/$(1)%.cpp.o: $(1)%.cpp $$(BUILD_DEPS)
	@echo Compiling $$(notdir $$@)...
	@mkdir -p $$(dir $$@)
	@$$(CXX) -MM -MP -MF "$$(@:%.o=%.d)" -MT "$$@" $(3) $(5) -E $$<
	@$$(CXX) -x c++ $(3) $(5) -c $$< -o $$@

endef

# $1 lib name
define generate_lib

$(1)_INC_DIRS += $$($(1)_LIB_DIRS)
$(1)_INC_FLAGS := $$(addprefix -iquote,$$($(1)_INC_DIRS))

$(1)_SYS_INC_FLAGS := $$(addprefix -I,$$($(1)_SYS_INC_DIRS))

$(1)_CPPFLAGS := \
  $$($(1)_INC_FLAGS) \
  $$($(1)_SYS_INC_FLAGS) \
  $$($(1)_CPPFLAGS) \

$(1)_LIB_SRCS := $$($(1)_LIB_FILES)

ifneq ($$($(1)_LIB_DIRS),)
$(1)_LIB_SRCS += $$(shell find $$($(1)_LIB_DIRS) -maxdepth 1 -name *.c -or -name *.s -or -name *.S)
endif

$(1)_LIB_OBJS := $$($(1)_LIB_SRCS:%=$$(BUILD_DIR)/%.o)
$(1)_LIB_DEPS := $$($(1)_LIB_SRCS:%=$$(BUILD_DIR)/%.d)

DEPS := $(DEPS) $(1)_LIB_DEPS

$$(BUILD_DIR)/$(1).lib: $$($1_LIB_OBJS)
	@echo Building $$(notdir $$@)...
	@mkdir -p $$(dir $$@)
	@$$(AR) rcs $$@ $$^

$$(eval $$(call generate_compilation_rules,$$($(1)_LIB_ROOT),$$($(1)_ASFLAGS),$$($(1)_CPPFLAGS),$$($(1)_CFLAGS),$$($(1)_CXXFLAGS)))

endef

.PHONY: all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex
	@$(SIZE) $<

$(foreach _lib,$(LIBS),$(eval $(call generate_lib,$(_lib))))

ifneq ($(LINKER_CFG),)
LINKER_CFG_ARG := -T $(LINKER_CFG)
endif

$(BUILD_DIR)/$(TARGET).elf: $(OBJS) $(LDLIBS)
	@echo Linking $(notdir $@)...
	@mkdir -p $(dir $@)
	@$(LD) $(LINKER_CFG_ARG) $(CPPFLAGS) $(LDFLAGS) $(OBJS) -Wl,--start-group $(LDLIBS) -Wl,--end-group -o $@

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	@echo Creating $(notdir $@)...
	@mkdir -p $(dir $@)
	@$(OBJCOPY) -O ihex $< $@

$(eval $(call generate_compilation_rules,,$(ASFLAGS),$(CPPFLAGS),$(CFLAGS),$(CXXFLAGS)))

.PHONY: clean
clean:
	@echo Cleaning...
	@$(RM) -rf $(BUILD_DIR)

-include $(DEPS)
