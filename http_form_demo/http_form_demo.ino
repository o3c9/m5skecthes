#include <M5Stack.h>
#include "WebServer.h"

#define MAX_CHAR_SIZE 31

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

WebServer server(80);

void setupWifi()
{
    // For WiFi Error
    WiFi.disconnect(true);
    delay(1000);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    M5.Lcd.setTextSize(4);
    M5.Lcd.setCursor(20, 20);
    M5.Lcd.println(WiFi.localIP());
}

void indexHandler()
{
    Serial.println("GET /");
    server.send(200, "application/json", "{\"message\":\"hello\"}");
}

typedef struct
{
    char name[MAX_CHAR_SIZE + 1];
    int value;
} param_t;

#define MAX_PARAM_COUNT 7

param_t params[MAX_PARAM_COUNT];
int params_count = 0;

/**
 * parse the index embedded in argName.
 *
 * names[1] returns 1
 * namess[7] returns -1
 */
int parseArrayArg(String argName, String key)
{
    if (argName.startsWith(key))
    {
        const char n = argName.charAt(key.length() + 1);
        int index = atoi(&n);
        if (index < MAX_PARAM_COUNT)
            return index;
    }
    return -1;
}

void parseParameters()
{
    int index = 0;
    for (int i = 0; i < server.args(); i++)
    {
        const String name = server.argName(i);
        if ((index = parseArrayArg(name, "names")) != -1)
        {
            strncpy(params[index].name, server.arg(i).c_str(), MAX_CHAR_SIZE);
        }
        else if ((index = parseArrayArg(name, "values")) != -1)
        {
            params[index].value = server.arg(i).toInt();
        }
        params_count = max(params_count, index + 1);
    }

    for (int i = 0; i < params_count; i++)
    {
        Serial.printf("[%d] name=%s value=%d\r\n", i, params[i].name, params[i].value);
    }
}

void postHandler()
{
    parseParameters();
    server.send(200, "application/json", "{\"result\":\"ok\"}");
}

void setup()
{
    M5.begin();
    delay(1000);
    setupWifi();

    server.on("/", indexHandler);
    server.on("/post", HTTP_POST, postHandler);
    server.begin();
}

void loop()
{
    server.handleClient();
}
