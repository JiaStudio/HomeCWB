#include "RemoteAirQualitySensor.h"

RemoteAirQualitySensor::RemoteAirQualitySensor(const char * name, String apiURL,
  const char ** jsonPath): Service::AirQualitySensor() {
  this -> name = name;
  this -> apiURL = apiURL;
  this -> jsonPath = jsonPath;

  airQuality = new Characteristic::AirQuality(2); // set initial air quality index
  fault = new Characteristic::StatusFault(1); // set initial state = fault
  ozoneDensity = new Characteristic::OzoneDensity(0); // set initial ozone density
  nitrogenDioxideDensity = new Characteristic::NitrogenDioxideDensity(0); // set initial nitrogen dioxide density
  sulphurDioxideDensity = new Characteristic::SulphurDioxideDensity(0); // set initial sulphur dioxide density
  pm25Density = new Characteristic::PM25Density(0); // set initial PM2.5 density
  pm10Density = new Characteristic::PM10Density(0); // set initial PM10 density
}


void RemoteAirQualitySensor::loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastApiCall >= apiInterval) {

    lastApiCall = currentMillis;
    String json = httpGet(apiURL.c_str());
    if (json.length() > 0) {
      //AQI
      int newAirQualityIndex = static_cast < int > (getValueFromJsonPathAndLastKey(json, jsonPath, "aqi"));
      if (newAirQualityIndex != -999) {
        airQualityIndex = newAirQualityIndex;
        int aqiLevel = convertAQItoLevel(airQualityIndex);
        airQuality -> setVal(aqiLevel); // update air quality index
        fault -> setVal(0); // clear fault

        // Ozone density
        float newOzoneDensity = getValueFromJsonPathAndLastKey(json, jsonPath, "o3");
        ozoneDensity->setVal(newOzoneDensity);

        // Nitrogen dioxide density
        float newNitrogenDioxideDensity = getValueFromJsonPathAndLastKey(json, jsonPath, "no2");
        nitrogenDioxideDensity->setVal(newNitrogenDioxideDensity);

        // Sulphur dioxide density
        float newSulphurDioxideDensity = getValueFromJsonPathAndLastKey(json, jsonPath, "so2");
        sulphurDioxideDensity->setVal(newSulphurDioxideDensity);

        // PM2.5 density
        float newPM25Density = getValueFromJsonPathAndLastKey(json, jsonPath, "pm2.5");
        pm25Density->setVal(newPM25Density);

        // PM10 density
        float newPM10Density = getValueFromJsonPathAndLastKey(json, jsonPath, "pm10");
        pm10Density->setVal(newPM10Density);

        LOG1("Sensor %s update: AirQualityIndex=%d, OzoneDensity=%.2f, NitrogenDioxideDensity=%.2f, SulphurDioxideDensity=%.2f, PM25Density=%.2f, PM10Density=%.2f\n",
          name, airQualityIndex, newOzoneDensity, newNitrogenDioxideDensity, newSulphurDioxideDensity, newPM25Density, newPM10Density);
      }
      
      if (airQualityIndex == -999 && !fault -> getVal()) { // if there is no current fault
        fault -> setVal(1); // set fault state
        LOG1("Sensor %s update: FAULT\n", name);
      }
    }
  }
}
