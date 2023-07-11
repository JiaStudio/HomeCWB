// ult.cpp
#include "ult.h"

String httpGet(const char * url) {
  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode == 200) {
    String payload = http.getString();
    http.end();
    return payload;
  } else {
    http.end();
    return "";
  }
}

float getValueFromJsonPath(String json, const char** path) {
  DynamicJsonDocument doc(json.length() * 2);
  DeserializationError error = deserializeJson(doc, json);

  if (error) {
    LOG1("deserializeJson() failed: ");
    LOG1(error.f_str());
    LOG1("\n");
    return -1.0f;
  }

  JsonVariant variant = doc;
  for (const char** p = path; *p != nullptr; p++) {
    if (variant.is<JsonObject>()) {
      variant = variant.getMember(*p);
    } else if (variant.is<JsonArray>()) {
      int index = atoi(*p);
      variant = variant.getElement(index);
    } else {
      return -999.0f;
    }
  }

  if (variant.is<int>()) {
    return static_cast<float>(variant.as<int>());
  } else if (variant.is<float>()) {
    return variant.as<float>();
  }

  // Convert string to float
  String variantString = variant.as<String>();
  float variantFloat = variantString.toFloat();

  if (variantString.length() > 0 && variantString.toFloat() == 0.0f) {
    // Check if the string contains only '0'
    bool allZeros = true;
    for (char c : variantString) {
      if (c != '0' && c != '.') {
        allZeros = false;
        break;
      }
    }
    if (allZeros) {
      return 0.0f;
    }
  } else if (variantFloat != 0.0f) {
    return variantFloat;
  }

  return -999.0f;
}

float getValueFromJsonPathAndLastKey(String json, const char** path, String lastKey) {
    // Create a new array of size + 1
    int size = 0;
    while (path[size]) {
        size++;
    }
    
    const char** result = new const char*[size + 2];

    // Copy the elements before the index 2
    for (int i = 0; i < 2; i++) {
        result[i] = path[i];
    }

    // Insert the new string at index 2
    char *newString = new char[lastKey.length() + 1];
    strcpy(newString, lastKey.c_str());
    result[2] = newString;

    // Copy the remaining elements after the index 2
    for (int i = 2; i < size; i++) {
        result[i + 1] = path[i];
    }

    // Set the last element to nullptr
    result[size + 1] = nullptr;

    float value = getValueFromJsonPath(json, result);

    // Clean up memory
    delete[] newString;
    delete[] result;

    return value;
}

int convertAQItoLevel(int aqi) {
  int level;

  if (aqi >= 0 && aqi <= 50) {
    level = 1;
  } else if (aqi >= 51 && aqi <= 100) {
    level = 2;
  } else if (aqi >= 101 && aqi <= 150) {
    level = 3;
  } else if (aqi >= 151 && aqi <= 200) {
    level = 4;
  } else if (aqi >= 201 && aqi <= 300) {
    level = 5;
  } else {
    level = 6;
  }

  return level;
}
