#include<ESP8266WiFi.h>
const char* ssid = "Bigcamp_FTTx"; //ssid ของ Wi-Fi ที่เราตอ้งการเชื่อมต่อค่ะ
const char* pass = "bc123456"; //password ของ Wi-Fi ที่เราตอ้งการเชื่อมต่อค่ะ
#include <DHT.h>
#define DHTPIN D4
#define DHTTYPE DHT22
char thingSpeakAddress[] = "api.thingspeak.com";
String writeAPIKey = "J4E0J2BU6KZ3ZB2I"; //เอา Write API Key ของเรามาใส่ค่ะ
WiFiClient client; //เรียกใชก้ารเชื่อมต่อกบั Wi-Fi
DHT dht (DHTPIN, DHTTYPE);
void setup() {
 Serial.begin(115200);
 WiFi.begin(ssid, pass);
 dht.begin();

 while (WiFi.status() != WL_CONNECTED) {
 Serial.print(".");
 delay(500);
 }

 Serial.println("");
 Serial.println("Wi-Fi connected");
 Serial.print("IP : ");
 Serial.println(WiFi.localIP());
}
void loop() {
 float t = dht.readTemperature();
 float h = dht.readHumidity();
 Serial.print("temp : ");
 Serial.println(t);
 Serial.print("hum : ");
 Serial.println(h);
 delay(1000);
 String temp = (String)t; //เนื่องจาก temp เป็ น float ซ่ึงจะส่งค่าไม่ได้เราจึกตอ้งแปลงเป็น String ก่อนค่ะ
 String hum = (String)h; //เนื่องจาก hum เป็ น float ซ่ึงจะส่งค่าไม่ได้เราจึกตอ้งแปลงเป็น String ก่อนค่ะ
 String data = "field1=" + temp + "&field2=" + hum; //ข้อมูล String ที่เราจะส่งค่าไปยงัThingSpeak ค่ะ
 if (client.connect(thingSpeakAddress, 80)) {
 Serial.println(data);
 client.print("POST /update HTTP/1.1\n"); //การส่งค่าขอ้ มูลผา่ น HTTP ค่ะ
 client.print("Host: api.thingspeak.com\n");
 client.print("Connection: close\n");
 client.print("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
 client.print("Content-Type: application/x-www-form-urlencoded\n");
 client.print("Content-Length: ");
 client.print(data.length());
 client.print("\n\n");
 client.print(data); //path ขอ้ มูลที่เราจะส่งค่าไปยงั ThingSpeak ค่ะ
 }
}
