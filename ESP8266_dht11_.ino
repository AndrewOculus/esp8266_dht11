//https://github.com/adidax/dht11
#include <dht11.h>
#include <ESP8266WiFi.h>

const char* ssid     = "TP-LINK";
const char* password = "pass";
const char* host = "smarthome.hostapp.com";
const int refreshTime = 5000;
dht11 DHT;
int timer = 0;
#define DHT11_PIN 2

void setup(){
  Serial.begin(9600);
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
}

void loop(){
  timer+=1;
  
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
    	String str = "test= Temp: "+stringOne + " Humid: " + stringHumid + " Reliability: " + chk;
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
  

 
}

