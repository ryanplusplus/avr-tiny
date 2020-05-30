ifeq ($(MCU),atmega328p)
HARDWARE_MANUAL_URL := http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf
DATASHEET_URL := http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf
endif

ifeq ($(MCU),attiny85)
HARDWARE_MANUAL_URL := http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf
DATASHEET_URL := http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf
endif

ifneq ($(HARDWARE_MANUAL_URL),)
.PHONY: hardware_manual
hardware_manual:
	xdg-open $(HARDWARE_MANUAL_URL)
else
.PHONY: hardware_manual
hardware_manual:
	$(error unknown micro, please edit docs.mk)
endif

ifneq ($(HARDWARE_MANUAL_URL),)
.PHONY: datasheet
datasheet:
	xdg-open $(DATASHEET_URL)
else
.PHONY: datasheet
datasheet:
	$(error unknown micro, please edit docs.mk)
endif
