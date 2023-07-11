#include "RemoteLeakSensor.h"

RemoteLeakSensor::RemoteLeakSensor(const char * name, String apiURL,
  const char ** jsonPath): Service::LeakSensor() {
  this -> name = name;
  this -> apiURL = apiURL;
  this -> jsonPath = jsonPath;

  leakDetected = new Characteristic::LeakDetected(0); // set initial leak status to 0 (not detected)
  fault = new Characteristic::StatusFault(1); // set initial state = fault
}

void RemoteLeakSensor::loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastApiCall >= apiInterval) {
    lastApiCall = currentMillis;
    String json = httpGet(apiURL.c_str());
    if (json.length() > 0) {
      float newRinValue = getValueFromJsonPath(json, jsonPath);
      if (newRinValue != -999) {
        leakStatus = newRinValue > 0 ? 1 : 0;
        leakDetected -> setVal(leakStatus); // update leak status
        fault -> setVal(0); // clear fault

        LOG1("Sensor %s update: Rain Detected=%d\n", name, newRinValue);
      }
    } else if (!fault -> getVal()) { // if there is no current fault
      fault -> setVal(1); // set fault state
      LOG1("Sensor %s update: FAULT\n", name);
    }
  }
}
