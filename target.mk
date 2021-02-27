TARGET := tiny
BUILD_DIR := ./build

MCU := atmega4809

PACK := Atmel.ATmega_DFP.1.6.364

# dwdebug or avrdude
UPLOAD_TYPE := dwdebug
AVRDUDE_PROGRAMMER_TYPE := dragon_isp
AVRDUDE_PROGRAMMER_ARGS :=
DWDEBUG_TOOL := ttyUSB0

# This almost certainly doesn't work with megaavr 0-series
EFUSE := 0xFD
HFUSE := 0x9E
LFUSE := 0xE2

DEFINES := \
	F_CPU=3333333UL \

SRC_FILES := \

SRC_DIRS := \
  src \

LIB_FILES := \

LIB_DIRS := \
  lib/tiny/src \

INC_DIRS := \
  lib/tiny/include \
  dfp/$(PACK)/include \


include makefile-worker.mk

.PHONY: dfp
dfp: dfp/$(PACK)/package.content

dfp/$(PACK)/package.content: dfp/download/$(PACK).atpack
	@unzip dfp/download/$(PACK).atpack -d dfp/$(PACK)
	@touch $@

dfp/download/$(PACK).atpack:
	@mkdir -p $(dir $@)
	@cd $(dir $@) && wget http://packs.download.atmel.com/$(PACK).atpack
