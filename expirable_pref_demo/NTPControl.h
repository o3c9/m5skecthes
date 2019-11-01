#ifndef _NTP_CONTROL_H_
#define _NTP_CONTROL_H_

#include <M5Stack.h>
#include "time.h"

const char *ntpServer = "ntp.jst.mfeed.ad.jp";
const long gmtOffset_sec = 9 * 3600;
const int daylightOffset_sec = 0;

void init_NTP();
time_t localTime();
String localTimeString();

#endif /* _NTP_CONTROL_H_ */
