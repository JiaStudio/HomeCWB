#pragma once

const char *ssid = ""; // 欲連接的 Wi-Fi 名稱
const char *password = ""; // 欲連接的 Wi-Fi 密碼
const char *pairingCode = "11111110"; // HomeKit 的配對碼
const String cwbApiKey = ""; // 氣象資料開放平臺 Api 授權碼 https://opendata.cwb.gov.tw/
const String epaApiKey = ""; // 環保署環境資料開放平臺 Api 授權碼 https://data.epa.gov.tw/
const String cwbStationId = "C0D670"; // 氣象觀測站的站號 https://e-service.cwb.gov.tw/wdps/obs/state.htm
const String aqiSiteID = "24"; // 空氣品質監測站的測站編號

//即時氣溫
String realtimeTempURL = "https://opendata.cwb.gov.tw/api/v1/rest/datastore/O-A0001-001?Authorization=" + cwbApiKey + "&stationId=" + cwbStationId + "&elementName=TEMP";
const char * realtimeTempJsonPaths[] = {
  "records",
  "location",
  "0",
  "weatherElement",
  "0",
  "elementValue",
  nullptr
};

//即時雨量
String realtimeRainURL = "https://opendata.cwb.gov.tw/api/v1/rest/datastore/O-A0002-001?Authorization=" + cwbApiKey + "&stationId=" + cwbStationId + "&elementName=MIN_10";
const char * realtimeRainJsonPaths[] = {
  "records",
  "location",
  "0",
  "weatherElement",
  "0",
  "elementValue",
  nullptr
};


//即時相對濕度
String realtimeHumdURL = "https://opendata.cwb.gov.tw/api/v1/rest/datastore/O-A0001-001?Authorization=" + cwbApiKey + "&stationId=" + cwbStationId + "&elementName=HUMD";
const char * realtimeHumdJsonPaths[] = {
  "records",
  "location",
  "0",
  "weatherElement",
  "0",
  "elementValue",
  nullptr
};

//AQI 空品指標
String realtimeAqiURL = "https://data.epa.gov.tw/api/v2/aqx_p_432?api_key=" + epaApiKey + "&filters=SiteId,EQ," + aqiSiteID + "&fields=o3,no2,so2,pm2.5,pm10,aqi";
const char * realtimeAqiJsonPaths[] = {
  "records",
  "0",
  nullptr
};
