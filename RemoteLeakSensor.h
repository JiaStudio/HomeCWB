#pragma once

#include <HomeSpan.h>
#include <ArduinoJson.h>
#include "ult.h"

struct RemoteLeakSensor: Service::LeakSensor {
  SpanCharacteristic * leakDetected;
  SpanCharacteristic * fault;
  String apiURL;
  const char * name;
  uint8_t leakStatus;
  unsigned long lastApiCall = 0;
  unsigned long apiInterval = 1000 * 60; // interval
  const char ** jsonPath;

  RemoteLeakSensor(const char * name, String apiURL, const char ** jsonPath);

  void loop();
};
