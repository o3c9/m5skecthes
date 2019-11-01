/*
 * Dr. Purdum Beginning C for Arduino Second Edition 2015
 *
 * Modified by o3c9 2019
 */

#include <M5Stack.h>

#define MAX_CHAR 10

int readline(char *str)
{
    char c;
    int index = 0;
    while (true)
    {
        if (Serial.available() > 0)
        {
            index = Serial.readBytesUntil('\n', str, MAX_CHAR);
            str[index] = '\0';
            break;
        }
    }
    return index;
}

bool isLeapYear(int year)
{
    return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

void setup()
{
    M5.begin();
    delay(100);
}

void loop()
{
    if (Serial.available() > 0)
    {
        int buffer;
        int year;
        char data[MAX_CHAR + 1];

        buffer = readline(data);

        year = atoi(data);
        Serial.print("Year: ");
        Serial.print(year);
        Serial.print(" is ");
        if (!isLeapYear(year))
        {
            Serial.print("not ");
        }
        Serial.println("a leap year");
    }
}
