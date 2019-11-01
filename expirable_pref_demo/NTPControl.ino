#include "NTPControl.h"

void init_NTP()
{
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

time_t localTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
    }
    time_t now;
    time(&now);
    return now;
}

String localTimeString()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return "";
    }
    char buf[30];
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S.000%z", &timeinfo);
    return String(buf);
}
