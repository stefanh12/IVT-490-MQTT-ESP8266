#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <SoftwareSerial.h>
#include <AsyncElegantOTA.h>
#include <Board_Identify.h>

#include "RemoteDebug.h"
#include "userdata.h"
#include "version.h"


//************* CONFIG DEBUG *****************************************************************************
//********************************************************************************************************
RemoteDebug Debug;     

//************* CONFIG OTHER GLOBALS *********************************************************************
//********************************************************************************************************



byte mac[6];                                                                    // Variable - MAC address
char myBuffer[15];                                                              // Variable - MAC string buffer
uint8_t MAC_array[6];                                                           // Variable -
char MAC_char[18];                                                              // Variable -
String texttosend;


WiFiClient espClient;                                                           // Initiate wifi
PubSubClient client(espClient);                                                 // Initiate MQTT
AsyncCallbackWebHandler webgethandler;


uint32_t mmLastTime = 0;                                                        // Variable -
uint32_t mmTimeSeconds = 0;                                                     // Variable -


SoftwareSerial swSer(rxpin, txpin, false);
String inputString;
boolean stringComplete = false;
char inChar;
int counter;
int commaPosition;
float ivt[50];

//************* SETUP WIFI SERVER ************************************************************************
//********************************************************************************************************
AsyncWebServer server(80);

float stringToFloat(String input){
  String stringTemp = input;
  char stfarray[stringTemp.length() + 1];
  stringTemp.toCharArray(stfarray, sizeof(stfarray));
  float stf = atof(stfarray);
  stringTemp = "";
  memset(stfarray, 0, sizeof stfarray);
  return stf; 
}


//************* SETUP WIFI *******************************************************************************
//********************************************************************************************************
void setup_wifi() {
  delay(20);

/** TELNET **/
  Debug.begin(device_hostname);                                                       // Initiaze the telnet server
  Debug.setResetCmdEnabled(true);                                               // Enable/disable (true/false) the reset command (true/false)
  Debug.showTime(false);                                                        // Enable/disable (true/false) timestamps
  Debug.showProfiler(false);                                                    // Enable/disable (true/false) Profiler - time between messages of Debug
  Debug.showDebugLevel(false);                                                  // Enable/disable (true/false) debug levels
  Debug.showColors(true);                                                       // Enable/disable (true/false) colors

  Serial.println("- - - - - - - - - - - - - - - - - - - - - - - - - - -");      // Block separator to serial interface
  Debug.println("- - - - - - - - - - - - - - - - - - - - - - - - - - -");       // Block separator to telnet debug interface
  Serial.println(device_hostname);                                                     // Send project name and version to serial interface
  Debug.println(device_hostname);                                                      // Send project name and version to telnet debug interface
  Serial.println("- - - - - - - - - - - - - - - - - - - - - - - - - - -");      // Block separator to serial interface
  Debug.println("- - - - - - - - - - - - - - - - - - - - - - - - - - -");       // Block separator to telnet debug interface
  Serial.println();                                                             // Send space to serial interface
  Debug.println();                                                              // Send space to telnet debug interface

  Serial.println();                                                             // Connecting to wifi network
  Serial.print("Connecting to "); Serial.println(ssid);                         // Send network name to serial interface
  Debug.printf("Connecting to "); Debug.println(ssid);                          // Send network name to telnet debug interface

  WiFi.config(ip, dns, gateway, subnet);                                        // Configure connection with IP, DNS, Gateway and subnet
  WiFi.mode(WIFI_STA);                                                          // Switch to STA mode
  WiFi.begin(ssid, password);                                                   // Start wifi connection with SSID and Password
  WiFi.macAddress(mac);                                                         // Get MAC address of the node

  while (WiFi.status() != WL_CONNECTED) {                                       // Wait until connected to wifi
    delay(500);
    Serial.print(".");
  }

  Serial.println();                                                             // Block space to serial interface
  Debug.println();                                                              // Block space to telnet debug interface
  Serial.println("WiFi connected");                                             // Send successful connection to serial interface
  Debug.println("WiFi connected");                                              // Send successful connection to telnet debug interface

  Serial.print("IP address is "); Serial.println(WiFi.localIP());               // Send IP address to serial interface
  Debug.printf("IP address is "); Debug.println(WiFi.localIP());                // Send IP address to telnet debug interface

  sprintf(myBuffer,"%02X:%02X:%02X:%02X:%02X:%02X",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);    // Get MAC address
  Serial.print("MAC address is "); Serial.println(myBuffer);                                      // Send MAC address to serial interface
  Debug.printf("MAC address is "); Debug.println(myBuffer);                                       // Send MAC address to telnet debug interface

}
void setRootGetResponse()
{
  texttosend = "\r\n"; 
  texttosend += "\r\n"; 
  texttosend += mqtt_description;
  texttosend += "\r\n"; 
  texttosend += "Set Descriptopn topic: "; 
  texttosend += mqtt_sub_set_description;
  texttosend += "\r\n"; 
  texttosend += device_hostname;
  texttosend += "\r\n"; 
  texttosend += VERSION;
  texttosend += "\r\n"; 
  texttosend += "Build: ";
  texttosend +=BUILD_NUMBER;
  texttosend += "\r\n\r\n";
  texttosend += "topics: \r\n";
   for(int i=0; i< mqtt_total_topics; i++){
    texttosend += mqtt_topics[i];
      texttosend += "\r\n"; 
  } 
  server.removeHandler(&webgethandler);
  webgethandler = server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", texttosend);
 });
  
}
//************* READ MQTT TOPIC **************************************************************************
//********************************************************************************************************
void callback(char* topic, byte* payload, unsigned int length) {
 

    Serial.println();                                                             // Block space to serial interface
    Debug.println();                                                              // Block space to telnet debug interface
    Serial.print("Message arrived for topic [");                                  // Send text to serial interface
    Debug.printf("Message arrived for topic [");                                  // Send text to telnet debug interface
    Serial.print(topic); Serial.print("] ");                                      // Send MQTT topic to serial interface
    Debug.printf(topic); Debug.printf("] ");                                      // Send MQTT topic to telnet debug interface    
    Serial.println(mqtt_sub_set_description);                                                             // Block space to serial interface
    Debug.println(mqtt_sub_set_description);                                                              // Block space to telnet debug interface


    mqtt_description = "";
   {
    Serial.println();                                                             // Block space to serial interface
    Debug.println();                                                              // Block space to telnet debug interface
    Serial.print("Message arrived for topic [");                                  // Send text to serial interface
    Debug.printf("Message arrived for topic [");                                  // Send text to telnet debug interface
    Serial.print(topic); Serial.print("] ");                                      // Send MQTT topic to serial interface
    Debug.printf(topic); Debug.printf("] ");                                      // Send MQTT topic to telnet debug interface    
    for (unsigned int i=0;i<length;i++) {
          mqtt_description += (char)payload[i];
        }
    Serial.println();        
    Serial.println("payload: ");        
    Serial.println(mqtt_description);    
    setRootGetResponse();    


  }
  
  {
    Serial.println();                                                             // Block space to serial interface
    Debug.println();                                                              // Block space to telnet debug interface
    Serial.print("Message arrived for topic [");                                  // Send text to serial interface
    Debug.printf("Message arrived for topic [");                                  // Send text to telnet debug interface
    Serial.print(topic); Serial.print("] ");                                      // Send MQTT topic to serial interface
    Debug.printf(topic); Debug.printf("] ");                                      // Send MQTT topic to telnet debug interface    
  }
  
}
//************* RECONNECT MQTT ***************************************************************************
//********************************************************************************************************
void reconnect() {

  while (!client.connected()) {                                                 // Loop until reconnected
    delay(5000);                                                                // Wait 5 seconds before retrying
    Serial.print("Attempting connection to MQTT server... ");                   // Send text to serial interface
    Debug.printf("Attempting connection to MQTT server... ");                   // Send text to telnet debug interface
    if (client.connect(
			device_hostname.c_str(), MQTT_USERNAME, MQTT_PASSWORD,
			MQTT_WILL_TOPIC.c_str(), MQTT_WILL_QOS, MQTT_WILL_RETAIN, MQTT_WILL_MESSAGE)) {		// Connect to MQTT broker
      Serial.println(" connected!");                                            // Send text to serial interface
      Debug.println(" connected!");                                             // Send text to telnet debug interface
      client.subscribe(mqtt_sub_set_description.c_str(),1);
    } 
    else {
      Serial.print("failed, rc=");                                              // Send text to serial interface
      Debug.printf("failed, rc=");                                              // Send text to telnet debug interface
      Serial.print(client.state());                                             // Send failure state to serial interface
      //Debug.printf(client.state());                                           // Send failure state to telnet debug interface
      Serial.println(" try again in 10 seconds");                               // Send text to serial interface
      Debug.println(" try again in 10 seconds!");                               // Send text to telnet debug interface
      delay(10000);                                                             // Wait 5 seconds before retrying
    }
  }
}

//************* SETUP ************************************************************************************
//********************************************************************************************************
void setup()
{
  pinMode(LED_pin, OUTPUT);                                                     // Configure internal LED pin as output.

  WiFi.macAddress(MAC_array);                                                   // NEWNEWNEW
  for (unsigned int iii = 0; iii < sizeof(MAC_array); ++iii){                            // NEWNEWNEW
    sprintf(MAC_char,"%s%02X:",MAC_char,MAC_array[iii]);                        // NEWNEWNEW
  }

  if (MDNS.begin("esp8266")) {                                                  //
    Serial.println("MDNS responder started");                                   //
  }                                                                             //

  unictopic = BoardIdentify::mcu;
  String tmpmac =  MAC_char;
  tmpmac.replace(":","");
  tmpmac.remove(0, tmpmac.length()-4);
  unictopic += "_";
  unictopic += tmpmac;
  mqtt_sub_set_description = unictopic + mqtt_sub_set_description;
  for(int i=0; i< mqtt_total_topics; i++){
    mqtt_topics[i] = unictopic; 
  }
  int ii =0;
  mqtt_topics[ii++] += mqtt_topic_1;
  mqtt_topics[ii++] += mqtt_topic_2;
  mqtt_topics[ii++] += mqtt_topic_3;
  mqtt_topics[ii++] += mqtt_topic_4;
  mqtt_topics[ii++] += mqtt_topic_5;
  mqtt_topics[ii++] += mqtt_topic_6;
  mqtt_topics[ii++] += mqtt_topic_7;
  mqtt_topics[ii++] += mqtt_topic_8;
  mqtt_topics[ii++] += mqtt_topic_9;
  mqtt_topics[ii++] += mqtt_topic_10;
  mqtt_topics[ii++] += mqtt_topic_11;
  mqtt_topics[ii++] += mqtt_topic_12;
  mqtt_topics[ii++] += mqtt_topic_13;
  mqtt_topics[ii++] += mqtt_topic_14;
  mqtt_topics[ii++] += mqtt_topic_15;
  mqtt_topics[ii++] += mqtt_topic_16;
  mqtt_topics[ii++] += mqtt_topic_17;
  mqtt_topics[ii++] += mqtt_topic_18;
  mqtt_topics[ii++] += mqtt_topic_19;
  mqtt_topics[ii++] += mqtt_topic_21;
  mqtt_topics[ii++] += mqtt_topic_22;
  mqtt_topics[ii++] += mqtt_topic_23;
  mqtt_topics[ii++] += mqtt_topic_24;
  mqtt_topics[ii++] += mqtt_topic_25;
  mqtt_topics[ii++] += mqtt_topic_26;
  mqtt_topics[ii++] += mqtt_topic_27;
  mqtt_topics[ii++] += mqtt_topic_28;
  mqtt_topics[ii++] += mqtt_topic_29;
  mqtt_topics[ii++] += mqtt_topic_30;
  mqtt_topics[ii++] += mqtt_topic_31;
  mqtt_topics[ii++] += mqtt_topic_32;
  mqtt_topics[ii++] += mqtt_topic_33;
  mqtt_topics[ii++] += mqtt_topic_34;
  mqtt_topics[ii++] += mqtt_topic_35;
  mqtt_topics[ii++] += mqtt_topic_36;
     
  MQTT_WILL_TOPIC = unictopic + MQTT_WILL_TOPIC;
  device_hostname += tmpmac;

  Serial.begin(115200);                                                         // Start serial interface
  setup_wifi();                                                                 // Start wifi
  client.setServer(MQTT_SERVER, MQTT_PORT);                                     //
  client.setCallback(callback);                                                 //



  Debug.begin(device_hostname);                                                 // Start Telnet server
  Serial.print(F("Board Type: "));
  Serial.println(BoardIdentify::type);
  Serial.print(F("Board Make: "));
  Serial.println(BoardIdentify::make);
  Serial.print(F("Board Model: "));
  Serial.println(BoardIdentify::model);
  Serial.print(F("Board MCU: "));
  Serial.println(BoardIdentify::mcu);
  Serial.println(unictopic);
  setRootGetResponse();


  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  delay(10);
  server.begin();
  Serial.begin(115200);
  swSer.begin(9600);
  delay(10);

}

void fetchSerial ()
{
  while(swSer.available() > 0)
  {
    inChar = swSer.read();
    if(inChar != 32){
      inputString += inChar;
    }
    delay(2);
  }
  inChar = '0';
  Serial.println(inputString);
  Debug.println(inputString);

  stringComplete = true;
}

void splitString ()
{ 
  commaPosition = inputString.indexOf(';');
  while(commaPosition >= 0)
  {
    commaPosition = inputString.indexOf(';');
    if(commaPosition != -1)
    {
      ivt[counter] = stringToFloat(inputString.substring(0,commaPosition));
      inputString = inputString.substring(commaPosition+1, inputString.length());    
    }
    else
    {
      if(inputString.length() > 0){
        ivt[counter] = stringToFloat(inputString.substring(0,commaPosition));
      }
    }
    counter++;
  }
  Debug.println(inputString);
  counter = 0;
  inputString = "";
  commaPosition = 0;
  String tosend;
  for(int i = 1; i < mqtt_total_topics; i++){
    
     tosend = ivt[i];
    client.publish(mqtt_topics[i-1].c_str(),tosend.c_str(), true);                    // Publish to MQTT topic
    Serial.println(mqtt_topics[i-1]);
    Serial.println(tosend);
    Serial.println();
    Debug.println(mqtt_topics[i-1]);
    Debug.println(tosend);
  }
  memset(ivt, 0, sizeof ivt);
  stringComplete = false;
 
}
void loop() {
  // put your main code here, to run repeatedly:
  AsyncElegantOTA.loop();

  for (int ii=1;ii<BRIGHT;ii++){                                              // Breath in
    digitalWrite(LED_pin, LOW);                                               // LED on
    delayMicroseconds(ii*10);                                                 // Wait
    digitalWrite(LED_pin, HIGH);                                              // LED off
    delayMicroseconds(PULSE-ii*10);                                           // Wait
    delay(0);                                                                 // Prevent watchdog firing
  }
  for (int ii=BRIGHT-1;ii>0;ii--){                                            // Breath out
    digitalWrite(LED_pin, LOW);                                               // LED on
    delayMicroseconds(ii*10);                                                 // Wait
    digitalWrite(LED_pin, HIGH);                                              // LED off
    delayMicroseconds(PULSE-ii*10);                                           // Wait
    ii--;
    delay(0);                                                                 // Prevent watchdog firing
  }
    delay(REST);                                                              // Pause before repeat

  if (!client.connected()) {                                                  // If client disconnects...
      reconnect();                                                            // ...connect again
  }

  client.loop();
  if(swSer.available() > 0)
  {
    fetchSerial();
  }
  if(stringComplete == true){
    delay(10);
    splitString();
    delay(50);
  }
  Debug.handle();                                                               // Remote debug over telnet
  yield();       
}