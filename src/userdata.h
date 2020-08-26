 

//************ CONFIG WIFI *******************************************************************************
// Configurations of your wifi network - Fixed IP is used because it's quicker than DHCP. IP address and
// and Hostname must be unique inside your network
//********************************************************************************************************
const char* ssid = "YOUR_SSID";                                                       // Wifi SSID
const char* password = "YOUR_PASSWORD";             // Wifi password


IPAddress ip;                                                    // IP address
IPAddress dns;                                                         // DNS server
IPAddress gateway;                                                  // Gateway
IPAddress subnet;                                                // Subnet mask

String unictopic;                                                               //Set by boardtype and last 4 numerals of MAC address

String device_hostname = "IVT_490_"    ;                                   // Hostname
String mqtt_description = " ";


//************* CONFIG MQTT ******************************************************************************
// Configurations of your MQTT server -
//********************************************************************************************************
const char* MQTT_SERVER = "xxx.xxx.xxx.xxx";                                      // MQTT server IP ou URL
int MQTT_PORT = 1883;                                                           // MQTT port
const char* MQTT_USERNAME = "MQTTUser";                                         // MQTT user
const char* MQTT_PASSWORD = "YOUR_PASSWORD";                                         // MQTT password

//************ MQTT LWT **********************************************************************************
// Configurations of your MQTT LWT - Define here the Last Will and Testment of your device. the MQTT broker and the
// payload for door open and closed
//********************************************************************************************************

  String MQTT_WILL_TOPIC = "/status";                                           // MQTT last will topic
  String mqtt_sub_set_description = "/IVT_490/setdesc";                         // MQTT sub to description used later in HTTP info page
                                                                                // for HA send examle in services / mqtt {"topic": "ESP8266_5ED7/IVT_490/setdesc", "payload":"IVT 495 Twin", "retain":"true"}


  const char* MQTT_WILL_MESSAGE = "Online";                                     // MQTT last will message
  int MQTT_WILL_QOS = 1;                                                        // MQTT last will QoS (0,1 or 2)
  int MQTT_WILL_RETAIN = 0;                                                     // MQTT last will retain (0 or 1)

//************ MQTT TOPICS *******************************************************************************
// Configurations of your MQTT topics - to match your MQTT broker
//********************************************************************************************************
#define mqtt_total_topics 36
String mqtt_topic_1  = "/IVT_490/framledn"; //ivt[1];; //Framledning
String mqtt_topic_2  = "/IVT_490/ute"; //ivt[2];; //Ute
String mqtt_topic_3  = "/IVT_490/tappvarmvtopp"; //ivt[3];; //Tappvarmvatten Topp
String mqtt_topic_4  = "/IVT_490/varmevmitt"; //ivt[4];; //Varmvatten Mitt
String mqtt_topic_5  = "/IVT_490/varmevbotton"; //ivt[5];; //Värmevatten Botten
String mqtt_topic_6  = "/IVT_490/inne"; //ivt[6];; //Rumstemp
String mqtt_topic_7  = "/IVT_490/hetgas"; //ivt[7];; //Hetgas
String mqtt_topic_8  = "/IVT_490/egtemp"; //ivt[8];; //Extra Acc-Tank
String mqtt_topic_9  = "/IVT_490/tryckvakt"; //ivt[9];; //Tryckvakt
String mqtt_topic_10  = "/IVT_490/hogtryck"; //ivt[10];; //Högtryck
String mqtt_topic_11  = "/IVT_490/lagtryck"; //ivt[11];; //Lågtryck
String mqtt_topic_12  = "/IVT_490/egsemester"; //ivt[12];; //Semester aktiv?
String mqtt_topic_13  = "/IVT_490/kompressor"; //ivt[13];; //Kompressor aktiv
String mqtt_topic_14  = "/IVT_490/schuntoppen"; //ivt[14];; //SV1 Öppna
String mqtt_topic_15  = "/IVT_490/schuntstangd"; //ivt[15];; //SV1 Stäng
String mqtt_topic_16  = "/IVT_490/cirkpump"; //ivt[16];; //P1 Rad
String mqtt_topic_17  = "/IVT_490/flakt"; //ivt[17];; //Fläkt
String mqtt_topic_18  = "/IVT_490/larm"; //ivt[18];; //Larm aktiv
String mqtt_topic_19  = "/IVT_490/Extern_P2"; //ivt[19];; //Extern P2
String mqtt_topic_20  = "/IVT_490/LLT_GT1"; //ivt[20];; //LLT GT1
String mqtt_topic_21  = "/IVT_490/LL_GT1"; //ivt[21];; //LL GT1
String mqtt_topic_22  = "/IVT_490/bvframledning"; //ivt[22];; //BV GT1
String mqtt_topic_23  = "/IVT_490/UL_GT1"; //ivt[23];; //UL GT1
String mqtt_topic_24  = "/IVT_490/LL_GT3_2"; //ivt[24];; //LL GT3:2
String mqtt_topic_25  = "/IVT_490/ULT_GT3_2"; //ivt[25];; //ULT GT3:2
String mqtt_topic_26  = "/IVT_490/UL_GT3_2"; //ivt[26];; //UL GT3:2
String mqtt_topic_27  = "/IVT_490/LL_GT3_3"; //ivt[27];; //LL GT3:3
String mqtt_topic_28  = "/IVT_490/BV_GT3_3"; //ivt[28];; //BV GT3:3
String mqtt_topic_29  = "/IVT_490/extravv1"; //ivt[29];; //SV3 BV Förskj
String mqtt_topic_30  = "/IVT_490/extravv2"; //ivt[30];; //Effekt ink vit VV behov
String mqtt_topic_31  = "/IVT_490/extravv3"; //ivt[31];; //Tillskotstimer VV behov
String mqtt_topic_32  = "/IVT_490/Tappvprio"; //ivt[32];  ; //Tappv prio
String mqtt_topic_33  = "/IVT_490/elpatron"; //ivt[33];; //Tillskott i %/10
String mqtt_topic_34  = "/IVT_490/Tillskott_RAD"; //ivt[34];; //Tillskott RAD
String mqtt_topic_35  = "/IVT_490/extravv4"; //ivt[35];; //Tillskott Tillägg
String mqtt_topic_36  = "/IVT_490/Default_SV2_Open"; //ivt[36];; //Default SV2 Open
String mqtt_topics[mqtt_total_topics+1];
//************* CONFIG PINS ******************************************************************************
//********************************************************************************************************
#define rxpin 14                                                                // Serial Recieve pin
#define txpin  -1 //12                                                                // Serial Transmit pin unused for now



//************* MISC configurations **********************************************************************
//********************************************************************************************************

int LED_pin = 2;                                                                // Internal LED in NodeMCU
#define BRIGHT 150                                                              // Maximum LED intensity (1-500)
#define INHALE 1500                                                             // Breathe-in time in milliseconds
#define PULSE INHALE*1000/BRIGHT                                                // Pulse
#define REST 1000                                                               // Pause between breathes
