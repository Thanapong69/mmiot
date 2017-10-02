/*  NETPIE ESP8266 blink                                   */

#include <ESP8266WiFi.h>
#include <MicroGear.h>

const char* ssid     = "Apple TV"; //your ssid
const char* password = "APPLE_TV"; //your password

#define APPID   "testNetpiebeforemidterm" //your AppID
#define KEY     "0HmuM9qMg7kzTZg" //your Key
#define SECRET  "0YluGHv3iyBOjQknl5cXgsIAq" //your Secret
#define ALIAS   "NodeMCU12E"

WiFiClient client;

int timer = 0;
char state = 0;
MicroGear microgear(client);

/* If a new message arrives, do this */
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
// If messaage = 1 On LED, If 0 LED off
    if(*(char *)msg == '1'){ 
        digitalWrite(LED_BUILTIN, LOW); // LED on 
      }else{ 
        digitalWrite(LED_BUILTIN, HIGH); // LED off }
    }
}

/*
void onFoundgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Found new member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();  
}

void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Lost member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();
}
*/

/* When a microgear is connected, do this */
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    /* Set the alias of this microgear ALIAS */
    microgear.setAlias(ALIAS);
}


void setup() {
    /* Add Event listeners */

    /* Call onMsghandler() when new message arraives */
    microgear.on(MESSAGE,onMsghandler);

    /* Call onFoundgear() when new gear appear */
    //microgear.on(PRESENT,onFoundgear);

    /* Call onLostgear() when some gear goes offline */
    //microgear.on(ABSENT,onLostgear);

    /* Call onConnected() when NETPIE connection is established */
    microgear.on(CONNECTED,onConnected);

    Serial.begin(115200);
    Serial.println("Starting...");

    pinMode(LED_BUILTIN, OUTPUT); //Set LED Built-in to Output

    /* Initial WIFI, this is just a basic method to configure WIFI on ESP8266.                       */
    /* You may want to use other method that is more complicated, but provide better user experience */
    if (WiFi.begin(ssid, password)) {
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    /* Initial with KEY, SECRET and also set the ALIAS here */
    microgear.init(KEY,SECRET,ALIAS);

    /* connect to NETPIE to a specific APPID */
    microgear.connect(APPID);
}

void loop() {
    /* To check if the microgear is still connected */
    if (microgear.connected()) {
        Serial.println("connected");

        /* Call this method regularly otherwise the connection may be lost */
        microgear.loop();

        if (timer >= 1000) {
            Serial.println("Publish...");

            //chat myself with invert stage
            if(state==0){
              microgear.chat(ALIAS,state);
              state = 1;
            }else{
              microgear.chat(ALIAS,state);
              state = 0;              
            }          
            timer = 0;
        } 
        else timer += 100;
    }
    else {
        Serial.println("connection lost, reconnect...");
        if (timer >= 5000) {
            microgear.connect(APPID);
            timer = 0;
        }
        else timer += 100;
    }
    delay(100);
}
