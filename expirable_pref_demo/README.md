# Expirable Preferences

A sketch for testing the preferences with expiration.
It's similar to `SETEX` in Redis.

It requires WiFi to get access to NTP server for the current time.

## Usage

```c
preferences.begin(PREF_NAME, false);

expirable_val_t item = getval(KEY_NAME);
item.value++;

// Print the counter to Serial Monitor
Serial.printf("Current counter value: %u (expire at %d, current = %d)\n", item.value, item.expired_at, localTime());

setvalex(KEY_NAME, &item, EXPIRES_IN_SECONDS);

preferences.end();
```
