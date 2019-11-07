ARDUINO := arduino-cli
BOARD := espressif:esp32:m5stack-core-esp32
PORT := /dev/cu.SLAB_USBtoUART
TTY := /dev/tty.SLAB_USBtoUART
BAUD := 115200
PROJECT := $(shell basename "$$PWD")
BUILD_DIR := $(realpath ../build/$(PROJECT))
BOARD_IN_PATH := $(subst :,.,$(BOARD))

.PHONY: upload
upload:
	cp $(BUILD_DIR)/$(PROJECT).ino.partitions.bin $(PROJECT).$(BOARD_IN_PATH).partitions.bin
	$(ARDUINO) upload -b $(BOARD) -p $(PORT) -t $$PWD

.PHONY: compile
compile:
	$(ARDUINO) compile -b $(BOARD) --build-path $(BUILD_DIR) --build-cache-path $(BUILD_DIR) $$PWD

.PHONY: serial
serial:
	screen $(TTY) $(BAUD)

.PHONY: clean
clean:
	rm -f *.bin
	rm -f *.elf

all: compile upload clean

.DEFAULT_GOAL := all
