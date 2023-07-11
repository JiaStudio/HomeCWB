#include "HomeSpan.h" 
#include "RemoteTempSensor.h"
#include "RemoteHumiditySensor.h"
#include "RemoteAirQualitySensor.h"
#include "RemoteLeakSensor.h"
#include "config.h" 

void setup() {

  Serial.begin(115200);
  homeSpan.setLogLevel(1);

  homeSpan.setWifiCredentials(ssid, password);
  homeSpan.setPairingCode(pairingCode);
  homeSpan.begin(Category::Bridges, "HomeCWB");

  // This first Accessory is the new "Bridge" Accessory.  It contains no functional Services, just the Accessory Information Service
  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();

  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  new Characteristic::Name("即時氣溫 - CWB");
  new RemoteTempSensor("即時氣溫", realtimeTempURL, realtimeTempJsonPaths);

  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  new Characteristic::Name("即時濕度 - CWB");
  new RemoteHumiditySensor("即時濕度", realtimeHumdURL, realtimeHumdJsonPaths);

  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  new Characteristic::Name("即時降雨 - CWB");
  new RemoteLeakSensor("即時降雨", realtimeRainURL, realtimeRainJsonPaths);

  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  new Characteristic::Name("空氣品質 - EPA");
  new RemoteAirQualitySensor("空氣品質", realtimeAqiURL, realtimeAqiJsonPaths);
  
} // end of setup()

void loop() {

  homeSpan.poll();

} // end of loop()
