#include "RemoteTempSensor.h"

RemoteTempSensor::RemoteTempSensor(const char * name, String apiURL, const char ** jsonPath): Service::TemperatureSensor() {
  this -> name = name;
  this -> apiURL = apiURL;
  this -> jsonPath = jsonPath;

  temp = new Characteristic::CurrentTemperature(-10.0); // set initial temperature
  temp -> setRange(-50, 100); // expand temperature range to allow negative values

  fault = new Characteristic::StatusFault(1); // set initial state = fault
}

void RemoteTempSensor::loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastApiCall >= apiInterval) {

    lastApiCall = currentMillis;
    String json = httpGet(apiURL.c_str());
    if (json.length() > 0) {
      float newTemperature = getValueFromJsonPath(json, jsonPath);
      if (newTemperature != -999) {
        temperature = newTemperature;
        temp -> setVal(temperature); // update temperature
        fault -> setVal(0); // clear fault

        LOG1("Sensor %s update: Temperature=%0.1f\n", name, temperature);
      }
    }

    // float newTemperature = getTemperatureFromApi();
  }

  if (temperature == -999 && !fault -> getVal()) { // if there is no current fault
    fault -> setVal(1); // set fault state
    LOG1("Sensor %s update: FAULT\n", name);
  }
}
