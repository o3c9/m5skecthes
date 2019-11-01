#include "ExpirablePreferences.h"

expirable_val_t getval(const char *key)
{
    expirable_val_t val;
    String data = preferences.getString(key);
    if (!data.isEmpty())
    {
        int idx = data.indexOf(":");
        int expired_at = data.substring(0, idx).toInt();
        String count_str = data.substring(idx + 1);

        time_t now = localTime();

        if (expired_at <= now)
        {
            // the key is already expired, so it will initialize the value...
            val.init(VAL_NOT_SET);
        }
        else
        {
            val.value = count_str.toInt();
            val.expired_at = expired_at;
        }
    }
    else
    {
        val.init(VAL_NOT_SET);
    }

    return val;
}

void setvalex(const char *key, expirable_val_t *val, int expires_in_sec)
{
    if (val->expired_at == NULL)
    {
        val->expired_at = localTime() + expires_in_sec;
    }

    char buf[30];
    snprintf(buf, sizeof(buf), "%d:%d", val->expired_at, val->value);
    preferences.putString(key, buf);
}
