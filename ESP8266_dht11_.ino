https://github.com/adidax/dht11
#include <dht11.h>
https://github.com/ekstrand/ESP8266wifi
#include <ESP8266WiFi.h>

#define DHT11_PIN 2//data pin for dth11

const char* ssid  = "TP-LINK";//you wifi name
const char* password = "pass";//your wifi pass
const char* host = "smarthome.hostapp.com";//your hosting adress
const unsigned long refreshTime = 5000; //send data to server after 5 second
unsigned long old_time;//vars for update
unsigned long new_time;//delta time 
dht11 DHT;//dht11 lib object
unsigned long timer = 0;//trigger timer


void setup(){
  //begin serial port
  Serial.begin(9600);
  //begin wi-fi connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
  }
}

void loop(){
  new_time = millis();
  unsigned long delta = new_time - old_time;
  timer+=delta;
  if(timer > refreshTime)
  {
  	//reset timer
  	timer = 0;
  	//read date from DHT11
  	int chk;
  	chk = DHT.read(DHT11_PIN); 
  	
  	Serial.print(DHT.humidity,1);
  	Serial.print(",\t");
  	Serial.println(DHT.temperature,1);
  
  	//wi-fi create GET response
  	WiFiClient client;
 
  	if (client.connect(host, 80))
  	{
    	client.print( "GET /index.php?");

    	String stringTemp =  String(DHT.temperature, DEC); 
    	String stringHumid = String(DHT.humidity , DEC);
    	String str = "temp="+stringTemp; //+ " Humid: " + stringHumid + " Reliability: " + chk;
    	client.print(str);
    	client.println( " HTTP/1.1");
    	client.print( "Host:" );
    	client.println(host);
    	client.println( "Connection: close" );
    	client.println();
    	client.println();
    	Serial.println("send to remote server");
  	}

  }
 old_time = new_time;
}

