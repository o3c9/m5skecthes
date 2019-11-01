#include <M5Stack.h>
#include <WiFi.h>

#include "ExpirablePreferences.h"

#ifdef WIFI_SSID
char *ssid = WIFI_SSID;
#else
char *ssid = "WIFI_SSID";
#endif

#ifdef WIFI_PASSWORD
char *password = WIFI_PASSWORD;
#else
char *password = "WIFI_PASSWORD";
#endif

#define PREF_NAME "pref"
#define KEY_NAME "key"
#define EXPIRES_IN_SECONDS (60 * 5)

Preferences preferences;

void increment()
{
    preferences.begin(PREF_NAME, false);

    expirable_val_t item = getval(KEY_NAME);
    item.value++;

    // Print the counter to Serial Monitor
    Serial.printf("Current counter value: %u (expire at %d, current = %d)\r\n", item.value, item.expired_at, localTime());

    setvalex(KEY_NAME, &item, EXPIRES_IN_SECONDS);

    preferences.end();
}

void setup()
{
    Serial.begin(115200);
    M5.begin();
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);

    //connect to WiFi
    Serial.printf("Connecting to %s ", ssid);
    WiFi.begin(ssid, password);
    int count = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(300);
        Serial.print(".");
        count++;
        if (count > 10)
        {
            count = 0;
            WiFi.mode(WIFI_STA);
            WiFi.disconnect();
            delay(100);
            WiFi.begin(ssid, password);
        }
    }
    Serial.println("CONNECTED");

    //init and get the time
    init_NTP();

    preferences.begin(PREF_NAME, false);
    preferences.clear();
    preferences.end();
}

void loop()
{
    increment();
    delay(1000);
}
