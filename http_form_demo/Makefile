ARDUINO := /Applications/Arduino.app/Contents/MacOS/Arduino
BUILD_DIR := ../build/$(shell basename "$$PWD")
BOARD := espressif:esp32:m5stack-core-esp32
PORT := /dev/cu.SLAB_USBtoUART
TTY := /dev/tty.SLAB_USBtoUART
BAUD := 115200
SKETCH = $(shell basename "$$PWD").ino
DEFINES := "-DWIFI_SSID=\"$$WIFI_SSID\" -DWIFI_PASSWORD=\"$$WIFI_PASSWORD\""

.PHONY: upload
upload:
	$(ARDUINO) --pref build.path=$(BUILD_DIR) --pref build.defines=$(DEFINES) --board $(BOARD) --port $(PORT) --upload $(SKETCH)

.PHONY: verify
verify:
	$(ARDUINO) --pref build.path=$(BUILD_DIR) --pref build.defines=$(DEFINES) --board $(BOARD) --port $(PORT) --verify $(SKETCH)

.PHONE: serial
serial:
	screen $(TTY) $(BAUD)

.DEFAULT_GOAL := verify
