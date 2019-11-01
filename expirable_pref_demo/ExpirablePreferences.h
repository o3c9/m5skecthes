#ifndef _EXPIRABLE_PREFERENCES_H_
#define _EXPIRABLE_PREFERENCES_H_

#include <Preferences.h>
#include "NTPControl.h"

#define VAL_NOT_SET -1

extern Preferences preferences;

typedef struct
{
    int value;
    time_t expired_at;

    void init(int init_val)
    {
        value = init_val;
        expired_at = NULL;
    }
} expirable_val_t;

expirable_val_t getval(const char *key);
void setvalex(const char *key, expirable_val_t *val, int expires_in_sec);

#endif /* _EXPIRABLE_PREFERENCES_H_ */
