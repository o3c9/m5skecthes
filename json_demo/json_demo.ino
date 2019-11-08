#include "cJSON.h"
#include <M5Stack.h>

const char *data = "{\"a\":1,\"str\":\"it's my json\",\"children\":[7,8,9],\"tags\":{\"Name\":\"o3c9\",\"Number\":1920}}";

void setup()
{
    M5.begin(false, false, true, false);

    // Parse JSON
    cJSON *doc = cJSON_Parse(data);
    int a = cJSON_GetObjectItem(doc, "a")->valueint;
    const char *s = cJSON_GetObjectItem(doc, "str")->valuestring;
    Serial.printf("[Parser] a=%d str=\"%s\" children=", a, s);
    cJSON *children = cJSON_GetObjectItem(doc, "children");
    for (int i = 0; i < cJSON_GetArraySize(children); i++)
    {
        cJSON *item = cJSON_GetArrayItem(children, i);
        Serial.printf("[%d]%d", i, item->valueint);
    }

    cJSON *tags = cJSON_GetObjectItem(doc, "tags");
    Serial.print(" tags={");
    cJSON *tag = tags->child;
    while (tag)
    {
        if (cJSON_IsString(tag))
        {
            Serial.printf("%s:\"%s\"", tag->string, tag->valuestring);
        }
        else
        {
            Serial.printf("%s:%d", tag->string, tag->valueint);
        }

        tag = tag->next;
        if (tag)
        {
            Serial.print(", ");
        }
    }

    Serial.println("}");

    cJSON_Delete(doc);

    // Create JSON

    cJSON *json, *jsonChildren, *jsonTags;
    json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "a", 1);
    cJSON_AddStringToObject(json, "str", "it's my json");
    jsonChildren = cJSON_AddArrayToObject(json, "children");
    cJSON_AddItemToArray(jsonChildren, cJSON_CreateNumber(7));
    cJSON_AddItemToArray(jsonChildren, cJSON_CreateNumber(8));
    cJSON_AddItemToArray(jsonChildren, cJSON_CreateNumber(9));
    jsonTags = cJSON_AddObjectToObject(json, "tags");
    cJSON_AddStringToObject(jsonTags, "Name", "o3c9");
    cJSON_AddNumberToObject(jsonTags, "Number", 1920);

    char *rendered = cJSON_PrintUnformatted(json);
    Serial.printf("[Encoder] %s", rendered);
    cJSON_Delete(json);
}

void loop()
{
}
