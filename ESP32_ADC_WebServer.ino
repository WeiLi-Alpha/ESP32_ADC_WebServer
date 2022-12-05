/*
 * ESP32 
 * Updates and Gets data from webpage without page refresh
 */
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <AsyncTCP.h>
#include "index.h"  //Web page header file
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ADC_PIN1 36
#define ADC_PIN2 39
#define ADC_PIN3 34
#define ADC_PIN4 35
#define ADC_PIN5 32
#define ADC_PIN6 33

int a_value=0;

WebServer server(80);


#ifdef __cplusplus
  extern "C" {
#endif
  uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif

uint8_t temprature_sens_read();


//Enter your SSID and PASSWORD
const char* ssid = "DukeVisitor";
const char* password = "";

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handleADC(int pin_index) {
 a_value = analogReadMilliVolts(pin_index);
 //Serial.println("-----------"+String(pin_index)+"-----------");
 //Serial.println(a_value);
 String adcValue = String(a_value);
 server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}

void handleDI(int pin_index, int value){
  digitalWrite(pin_index, value);
}

void handleADC_1() {
  handleADC(ADC_PIN1);
}
void handleADC_2() {
  handleADC(ADC_PIN2);
}
void handleADC_3() {
  handleADC(ADC_PIN3);
}
void handleADC_4() {
  handleADC(ADC_PIN4);
}
void handleADC_5() {
  handleADC(ADC_PIN5);
}
void handleADC_6() {
  handleADC(ADC_PIN6);
}

void handleTemp() {
 double atemp = (temprature_sens_read() - 32) / 1.8;
// Serial.println("-----------handleTemp-----------");
// Serial.println(atemp);
 String atemp_value = String(atemp);
 
 server.send(200, "text/plane", atemp_value); //Send temperature value only to client ajax request
}

//===============================================================
// Setup
//===============================================================

void setup(void){
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");

  a_value = analogRead(33);
  Serial.printf("a_value=%d\n",a_value);
  //pinMode(14, INPUT);

//ESP32 connects to your wifi -----------------------------------
  WiFi.mode(WIFI_STA); //Connectto your wifi
  WiFi.begin(ssid, password);

  Serial.println("Connecting to ");
  Serial.print(ssid);

  //Wait for WiFi to connect
  while(WiFi.waitForConnectResult() != WL_CONNECTED){      
      Serial.print(".");
    }
    
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
//----------------------------------------------------------------
 
  server.on("/", handleRoot);      //This is display page
  server.on("/handleTemp", handleTemp);//To get update of ADC Value only
  server.on("/handleADC1", handleADC_1);//To get update of ADC Value only
  server.on("/handleADC2", handleADC_2);//To get update of ADC Value only
  server.on("/handleADC3", handleADC_3);//To get update of ADC Value only
  server.on("/handleADC4", handleADC_4);//To get update of ADC Value only
  server.on("/handleADC5", handleADC_5);//To get update of ADC Value only
  server.on("/handleADC6", handleADC_6);//To get update of ADC Value only

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void loop(void){
  server.handleClient();
  delay(10);
}