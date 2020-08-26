Platformio code for using a ESP8266 to read the serial data from a IVT-490 series heat pump. 

The project is based on https://github.com/mskorge/ivt490-esp8266 and https://github.com/jorgeassuncao/MAID-EM 

Each value will be sent to a MQTT server where the main topic is #board#MAC" and a subtopic for each value

There is a webserver that you can use to update the firmware too.


Using Home Assistant I have the following configuration:
<code>
- platform: mqtt
  device_class: temperature 
  name: "IVT_495_framledning_temp"
  state_topic: 'ESP8266_5ED7/IVT_490/framledn'
  unit_of_measurement: '°C'
  value_template: "{{ ( value | float  / 10 ) }}"
- platform: mqtt
  device_class: temperature 
  name: "IVT_495_ute_temp"
  state_topic: 'ESP8266_5ED7/IVT_490/ute'
  unit_of_measurement: '°C'
  value_template: "{{ ( value | float  / 10 ) }}"
- platform: mqtt
  device_class: temperature 
  name: "IVT_495_tappvarmvtopp_temp"
  state_topic: 'ESP8266_5ED7/IVT_490/tappvarmvtopp'
  unit_of_measurement: '°C'
  value_template: "{{ ( value | float  / 10 ) }}"
- platform: mqtt
  device_class: temperature 
  name: "IVT_495_varmevmitt_temp"
  state_topic: 'ESP8266_5ED7/IVT_490/varmevmitt'
  unit_of_measurement: '°C'
  value_template: "{{ ( value | float  / 10 ) }}"
- platform: mqtt
  device_class: temperature 
  name: "IVT_495_varmevbotton_temp"
  state_topic: 'ESP8266_5ED7/IVT_490/varmevbotton'
  unit_of_measurement: '°C'
  value_template: "{{ ( value | float  / 10 ) }}"
- platform: mqtt
  device_class: temperature 
  name: "IVT_495_inne_temp"
  state_topic: 'ESP8266_5ED7/IVT_490/inne'
  unit_of_measurement: '°C'
  value_template: "{{ ( value | float  / 10 ) }}"
- platform: mqtt
  device_class: temperature 
  name: "IVT_495_hetgas_temp"
  state_topic: 'ESP8266_5ED7/IVT_490/hetgas'
  unit_of_measurement: '°C'
  value_template: "{{ ( value | float  / 10 ) }}"
- platform: mqtt
  device_class: temperature 
  name: "IVT_495_egtemp_temp"
  state_topic: 'ESP8266_5ED7/IVT_490/egtemp'
  unit_of_measurement: '°C'
  value_template: "{{ ( value | float  / 10 ) }}"
- platform: mqtt
  name: "IVT_495_tryckvakt"
  state_topic: 'ESP8266_5ED7/IVT_490/tryckvakt'
- platform: mqtt
  name: "IVT_495_hogtryck"
  state_topic: 'ESP8266_5ED7/IVT_490/hogtryck'
- platform: mqtt
  name: "IVT_495_lagtryck"
  state_topic: 'ESP8266_5ED7/IVT_490/lagtryck'
- platform: mqtt
  name: "IVT_495_egsemester"
  state_topic: 'ESP8266_5ED7/IVT_490/egsemester'
- platform: mqtt
  name: "IVT_495_kompressor"
  state_topic: 'ESP8266_5ED7/IVT_490/kompressor'
- platform: mqtt
  name: "IVT_495_schuntoppen"
  state_topic: 'ESP8266_5ED7/IVT_490/schuntoppen'
- platform: mqtt
  name: "IVT_495_schuntstangd"
  state_topic: 'ESP8266_5ED7/IVT_490/schuntstangd'
- platform: mqtt
  name: "IVT_495_cirkpump"
  state_topic: 'ESP8266_5ED7/IVT_490/cirkpump'
- platform: mqtt
  name: "IVT_495_flakt"
  state_topic: 'ESP8266_5ED7/IVT_490/flakt'
- platform: mqtt
  name: "IVT_495_larm"
  state_topic: 'ESP8266_5ED7/IVT_490/larm'
- platform: mqtt
  name: "IVT_495_Extern_P2"
  state_topic: 'ESP8266_5ED7/IVT_490/Extern_P2'
- platform: mqtt
  device_class: temperature 
  name: "IVT_495_LL_GT1"
  state_topic: 'ESP8266_5ED7/IVT_490/LL_GT1'
  unit_of_measurement: '°C'
  value_template: "{{ ( value | float  / 10 ) }}"
- platform: mqtt
  device_class: temperature 
  name: "IVT_495_bvframledning"
  state_topic: 'ESP8266_5ED7/IVT_490/bvframledning'
  unit_of_measurement: '°C'
  value_template: "{{ ( value | float  / 10 ) }}"
- platform: mqtt
  device_class: temperature 
  name: "IVT_495_UL_GT1"
  state_topic: 'ESP8266_5ED7/IVT_490/UL_GT1'
  unit_of_measurement: '°C'
  value_template: "{{ ( value | float  / 10 ) }}"
- platform: mqtt
  device_class: temperature 
  name: "IVT_495_LL_GT3_2"
  state_topic: 'ESP8266_5ED7/IVT_490/LL_GT3_2'
  unit_of_measurement: '°C'
  value_template: "{{ ( value | float  / 10 ) }}"
- platform: mqtt
  device_class: temperature 
  name: "IVT_495_ULT_GT3_2"
  state_topic: 'ESP8266_5ED7/IVT_490/ULT_GT3_2'
  unit_of_measurement: '°C'
  value_template: "{{ ( value | float  / 10 ) }}"
- platform: mqtt
  device_class: temperature 
  name: "IVT_495_UL_GT3_2"
  state_topic: 'ESP8266_5ED7/IVT_490/UL_GT3_2'
  unit_of_measurement: '°C'
  value_template: "{{ ( value | float  / 10 ) }}"
- platform: mqtt
  device_class: temperature 
  name: "IVT_495_LL_GT3_3"
  state_topic: 'ESP8266_5ED7/IVT_490/LL_GT3_3'
  unit_of_measurement: '°C'
  value_template: "{{ ( value | float  / 10 ) }}"
- platform: mqtt
  device_class: temperature 
  name: "IVT_495_BV_GT3_3"
  state_topic: 'ESP8266_5ED7/IVT_490/BV_GT3_3'
  unit_of_measurement: '°C'
  value_template: "{{ ( value | float  / 10 ) }}"
- platform: mqtt
  device_class: temperature 
  name: "IVT_495_extravv1"
  state_topic: 'ESP8266_5ED7/IVT_490/extravv1'
  unit_of_measurement: '°C'
  value_template: "{{ ( value | float  / 10 ) }}"
- platform: mqtt
  device_class: temperature 
  name: "IVT_495_extravv2"
  state_topic: 'ESP8266_5ED7/IVT_490/extravv2'
  unit_of_measurement: '°C'
  value_template: "{{ ( value | float  / 10 ) }}"
- platform: mqtt
  device_class: temperature 
  name: "IVT_495_extravv3"
  state_topic: 'ESP8266_5ED7/IVT_490/extravv3'
  unit_of_measurement: '°C'
  value_template: "{{ ( value | float  / 10 ) }}"
- platform: mqtt
  name: "IVT_495_Tappv prio"
  state_topic: 'ESP8266_5ED7/IVT_490/Tappv prio'
- platform: mqtt
  name: "IVT_495_elpatron"
  state_topic: 'ESP8266_5ED7/IVT_490/elpatron'
- platform: mqtt
  name: "IVT_495_Tillskott_RAD"
  state_topic: 'ESP8266_5ED7/IVT_490/Tillskott_RAD'
- platform: mqtt
  name: "IVT_495_extravv4"
  state_topic: 'ESP8266_5ED7/IVT_490/extravv4'
- platform: mqtt
  name: "IVT_495_Default_SV2_Open"
  state_topic: 'ESP8266_5ED7/IVT_490/Default_SV2_Open'
  </code>
