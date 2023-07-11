#pragma once

#include <HomeSpan.h>
#include <ArduinoJson.h>
#include "ult.h"

struct RemoteAirQualitySensor: Service::AirQualitySensor {
  SpanCharacteristic * airQuality;
  SpanCharacteristic * fault;
  SpanCharacteristic * ozoneDensity;
  SpanCharacteristic * nitrogenDioxideDensity;
  SpanCharacteristic * sulphurDioxideDensity;
  SpanCharacteristic * pm25Density;
  SpanCharacteristic * pm10Density;
  String apiURL;
  const char * name;
  uint8_t airQualityIndex;
  unsigned long lastApiCall = 0;
  unsigned long apiInterval = 1000 * 60; // interval
  const char ** jsonPath;

  RemoteAirQualitySensor(const char * name, String apiURL, const char ** jsonPath);

  void loop();
};
