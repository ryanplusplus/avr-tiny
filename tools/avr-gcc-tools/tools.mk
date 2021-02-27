ifneq ($(PACK),)
BUILD_DEPS += dfp
SYS_INC_DIRS += dfp/$(PACK)/include
endif

TOOLCHAIN_PREFIX := avr-
include $(dir $(realpath $(lastword $(MAKEFILE_LIST))))gcc.mk

.PHONY: dfp
dfp: dfp/$(PACK)/package.content

dfp/$(PACK)/package.content: dfp/download/$(PACK).atpack
	@unzip dfp/download/$(PACK).atpack -d dfp/$(PACK)
	@touch $@

dfp/download/$(PACK).atpack:
	@mkdir -p $(dir $@)
	@cd $(dir $@) && wget http://packs.download.atmel.com/$(PACK).atpack
