#pragma once

#include <HomeSpan.h>
#include <ArduinoJson.h>
#include "ult.h"

struct RemoteHumiditySensor: Service::HumiditySensor {
  SpanCharacteristic * humidity;
  SpanCharacteristic * fault;
  String apiURL;
  const char * name;
  float humidityValue;
  unsigned long lastApiCall = 0;
  unsigned long apiInterval = 1000 * 60; // interval
  const char ** jsonPath;

  RemoteHumiditySensor(const char * name, String apiURL, const char ** jsonPath);

  void loop();
};
