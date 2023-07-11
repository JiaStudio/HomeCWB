#include "RemoteHumiditySensor.h"

RemoteHumiditySensor::RemoteHumiditySensor(const char * name, String apiURL,
  const char ** jsonPath): Service::HumiditySensor() {
  this -> name = name;
  this -> apiURL = apiURL;
  this -> jsonPath = jsonPath;

  humidity = new Characteristic::CurrentRelativeHumidity(0.0); // set initial humidity
  humidity -> setRange(0, 100); // set humidity range

  fault = new Characteristic::StatusFault(1); // set initial state = fault
}

void RemoteHumiditySensor::loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastApiCall >= apiInterval) {

    lastApiCall = currentMillis;
    String json = httpGet(apiURL.c_str());
    if (json.length() > 0) {
      float newHumidity = getValueFromJsonPath(json, jsonPath);
      if (newHumidity != -999) {
        newHumidity = newHumidity * 100;
        humidityValue = newHumidity;
        humidity -> setVal(humidityValue); // update humidity
        fault -> setVal(0); // clear fault

        LOG1("Sensor %s update: Humidity=%0.0f%\n", name, humidityValue);
      }
    }

    // float newHumidity = getHumidityFromApi();
  }

  if (humidityValue == -999 && !fault -> getVal()) { // if there is no current fault
    fault -> setVal(1); // set fault state
    LOG1("Sensor %s update: FAULT\n", name);
  }
}
