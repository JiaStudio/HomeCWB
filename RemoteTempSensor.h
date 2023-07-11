#pragma once

#include <HomeSpan.h>
#include <ArduinoJson.h>
#include "ult.h"

struct RemoteTempSensor: Service::TemperatureSensor {
  SpanCharacteristic * temp;
  SpanCharacteristic * fault;
  String apiURL;
  const char * name;
  float temperature;
  unsigned long lastApiCall = 0;
  unsigned long apiInterval = 1000 * 60; // interval
  const char ** jsonPath;

  RemoteTempSensor(const char * name, String apiURL, const char ** jsonPath);

  void loop();
};
