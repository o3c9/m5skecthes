#include <nvs.h>
#include <nvs_flash.h>
#include <M5Stack.h>

void setup()
{
    Serial.begin(115200);
    int err;
    err = nvs_flash_init();
    Serial.printf("nvs_flash_init: %d\n", err);
    err = nvs_flash_erase();
    Serial.printf("nvs_flash_erase: %d\n", err);
}

void loop()
{
}
