// ult.h
#pragma once
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <HomeSpan.h>

String httpGet(const char * url);

float getValueFromJsonPath(String json, const char** path);

float getValueFromJsonPathAndLastKey(String json, const char** path, String lastKey);

int convertAQItoLevel(int aqi);
