
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>



// Network Credentials
const char* network_name     = "VFLAtt";
const char* wifi_password = "VFLGforever12!";
//My server name on my Ubuntu VM
const char* host = "http://192.168.1.196/post-esp-data.php"; //Host is my server hosted on Linux VM.
String api_key = "12345"; // API key value, will be changed later.


void setup() {

  Serial.begin(115200);
  delay(1000); 
  WiFi.begin(network_name, wifi_password); //Begin wifi connection using wifi password and network name.

  while(WiFi.status() != WL_CONNECTED)  //if wifi isn't connected, continue to try to connect.
  { 
    delay(500);
  }


}

void loop() {
  
  if(WiFi.status()== WL_CONNECTED)
  {
    //Send HTTP message every 5 seconds. This will eventually be changed to be dependent on each different sensor.
    delay(500); 
    WiFiClient client;
    HTTPClient http;
    String http_message;
    int http_send_message;

    http.begin(client, host);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String sensor_name, x, y, z, table_name,value, time;
    sensor_name = "Heart";
    table_name = "Heart";
    value = "1";
    time = "1";
    http_message = "api_key=" + api_key + "&" + "table_name=" + table_name + "&" + "sensor_name=" + sensor_name + "&" + "value=" + value + "&" + "time=" + time;
    http_send_message = http.POST(http_message);

    sensor_name = "Oxygen";
    table_name = "Oxygen";
    value = "2";
    time = "1";
    http_message = "api_key=" + api_key + "&" + "table_name=" + table_name + "&" + "sensor_name=" + sensor_name + "&" + "value=" + value + "&" + "time=" + time;
    http_send_message = http.POST(http_message);

    sensor_name = "Accelerometer";
    table_name = "Accelerometer";
    x = "1";
    y = "1";
    z = "1";
    time = "1";
    http_message = "api_key=" + api_key + "&" + "table_name=" + table_name + "&" + "sensor_name=" + sensor_name + "&" + "x=" + x + "&" + "y=" + y + "&" + "z=" + z + "&" + "time=" + time;
    http_send_message = http.POST(http_message);

    http.end(); //End http before next loop iteration.
  }

   
}