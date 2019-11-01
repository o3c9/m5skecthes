/*
 * Dr. Purdum Beginning C for Arduino Second Edition 2015
 *
 * Modified by o3c9 2019
 */

#include <M5Stack.h>

#define HEAD_PIN 21
#define TAIL_PIN 22

#define PAUSE 1000

int heads = 0;
int tails = 0;
long loops = 0;
long rN = 0L;

void setup()
{
    M5.begin();
    delay(10);

    pinMode(HEAD_PIN, OUTPUT);
    pinMode(TAIL_PIN, OUTPUT);

    randomSeed(analogRead(0));
}

void loop()
{
    rN = random(0, 1000000);
    digitalWrite(HEAD_PIN, LOW);
    digitalWrite(TAIL_PIN, LOW);

    delay(PAUSE);

    if (rN % 2 == 0)
    {
        digitalWrite(HEAD_PIN, HIGH);
        heads++;
    }
    else
    {
        digitalWrite(TAIL_PIN, HIGH);
        tails++;
    }

    loops++;

    if (loops % 50 == 0)
    {
        Serial.printf("After %d coin flips, heads = %d and tails = %d\n", loops, heads, tails);
    }

    delay(PAUSE);
}
