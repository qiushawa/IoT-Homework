#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>

// =================== 定義與常數 ===================
#define DETPIN 25
#define DETTYPE DHT22

// WiFi 參數
char ssid[] = "WIFI SSID";
char password[] = "WIFI PASWORD"; 

// ThingSpeak API 參數
String url = "https://api.thingspeak.com/update?api_key=API_KEY";

// =================== 物件宣告 ===================
DHT dht(DETPIN, DETTYPE);

// =================== 初始化函式 ===================
void setup() {
    Serial.begin(9600);

    // DHT 模組初始化
    Serial.println("DHTxx 初始化");
    dht.begin();

    // WiFi 連線
    Serial.println("連接到 WiFi: ");
    Serial.println(ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("\nWiFi 連線完成");
}

// =================== 主迴圈函式 ===================
void loop() {
    // 讀取溫濕度資料
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    // 顯示溫濕度資料
    Serial.print("濕度: ");
    Serial.println(humidity);
    Serial.print("溫度: ");
    Serial.println(temperature);

    // 連線到網頁並傳送資料
    Serial.println("啟動網頁連線");
    HTTPClient http;
    String url1 = url + "&field1=" + temperature + "&field2=" + humidity;

    // HTTP GET 請求
    http.begin(url1);
    int httpCode = http.GET();

    // 檢查 HTTP 回應
    if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.print("網頁內容: ");
        Serial.println(payload);
    } else {
        Serial.println("網路傳送失敗");
    }
    
    // 結束 HTTP 請求
    http.end();

    // 延遲 20 秒
    delay(20000);
}
