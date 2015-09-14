
#include <LWiFi.h>
#include <LWiFiClient.h>
#include <Wire.h>
#include <LDateTime.h>
#include <Utils.h>
#include <AmazonKinesisClient.h>
#include <MtkAWSImplementations.h>


AmazonKinesisClient kClient;

/* Device independent implementations required for AmazonDynamoDBClient to
 * function. */
MtkHttpClient httpClient;
//kinesis

MtkDateTimeProvider dateTimeProvider;




// It is an Arduino hack to include libraries that are referenced in other libraries. 
// For example WiFi is used in AWS libraries but we still need to include in the main sketch file for it to be recognized.


#include <stdlib.h>
#include <stdio.h>
#include "dht11.h"
#define dht_dpin 1 //no ; here. Set equal to channel sensor is on
dht11 DHT;

const int LightSensorPin = A0;  // Analog input pin that the potentiometer is attached to
float lightsensorValue = 0;

const int pirPin = 2;    //the digital pin connected to the PIR sensor's output
float motionvalue = 0;


char GUID1[] = "xxxxxxxx-2222-xxxx-xxxx-xxxxxxxxxxxx";
char GUID2[] = "yyyyyyyy-2222-yyyy-yyyy-yyyyyyyyyyyy";
char GUID3[] = "zzzzzzzz-2222-zzzz-zzzz-zzzzzzzzzzzz";
char GUID4[] = "aaaaaaaa-2222-aaaa-aaaa-aaaaaaaaaaaa";
char Org[] = "Microsoft Singapore DX Team";
char Disp[] = "Arduino + Raspiberry Pi 2 on Windows";
char Locn[] = "SG MIC";
char Measure1[] = "temperature";
char Units1[] = "C";
char Measure2[] = "humidity";
char Units2[] = "%";
char Measure3[] = "light";
char Units3[] = "lumen";
char Measure4[] = "motion";
char Units4[] = "binary";
char buffer[300];
char dtostrfbuffer[15];

// It is an Arduino hack to include libraries that are referenced in other libraries. 
// For example WiFi is used in AWS libraries but we still need to include in the main sketch file for it to be recognized.

void setup() {
  	/* Begin serial communication. */
	Serial.begin(115200);
       
        Serial.println("Begin Setup..");
        
        // Connect to WiFi (function loops until successful connection is made)
	Mtk_Wifi_Setup("ssid", "password");

        printWifiStatus();
        Serial.println("Wi-Fi connected");
        delay(500);
         KinesisClient_Setup();
        delay(500);
        Serial.println("Sensors connected");
        //dreamtcs to change
        Serial.println("Client connected");
	
	Serial.println("Setup complete! Looping main program");
	Serial.println("Initial mode: KINESIS");      


}


void loop() {                

	
	if (true) {
            //This is the "heart" of the program.
            DHT.read(dht_dpin);
            lightsensorValue = get_light_level();
            motionvalue = digitalRead(pirPin);
          
            float temperatureC = DHT.temperature;

            memset(buffer, '\0', sizeof(buffer));
            strcat(buffer, "{");
            strcat(buffer, "\"guid\":\"");
            strcat(buffer, GUID1);
            strcat(buffer, "\",\"organization\":\"");
            strcat(buffer, Org);
            strcat(buffer, "\",\"timecreated\":\"");
            strcat(buffer, "timenow");
            strcat(buffer, "\",\"displayname\":\"");
            strcat(buffer, Disp);
            strcat(buffer, "\",\"location\":\"");
            strcat(buffer, Locn);
            strcat(buffer, "\",\"measurename\":\"");
            strcat(buffer, Measure1);
            strcat(buffer, "\",\"unitofmeasure\":\"");
            strcat(buffer, Units1);
            strcat(buffer, "\",\"value\":");
            strcat(buffer, dtostrf(temperatureC, 5, 2, dtostrfbuffer));
            strcat(buffer, "}");
            Serial.println(buffer);
 putKinesis(GUID1,Org,Disp,Locn,Measure1,Units1,dtostrf(temperatureC, 5, 2, dtostrfbuffer));
//kClient.putRecord(buffer);

			
            delay(500);
            // print string for humidity, separated by line for ease of reading
            memset(buffer, '\0', sizeof(buffer));
            strcat(buffer, "{");
            strcat(buffer, "\"guid\":\"");
            strcat(buffer, GUID2);
            strcat(buffer, "\",\"organization\":\"");
            strcat(buffer, Org);
            strcat(buffer, "\",\"timecreated\":\"");
            strcat(buffer, "timenow");
            strcat(buffer, "\",\"displayname\":\"");
            strcat(buffer, Disp);
            strcat(buffer, "\",\"location\":\"");
            strcat(buffer, Locn);
            strcat(buffer, "\",\"measurename\":\"");
            strcat(buffer, Measure2);
            strcat(buffer, "\",\"unitofmeasure\":\"");
            strcat(buffer, Units2);
            strcat(buffer, "\",\"value\":");
            //strcat(buffer, dtostrf(10, 5, 2, dtostrfbuffer));
            strcat(buffer, dtostrf(DHT.humidity, 5, 2, dtostrfbuffer));
            strcat(buffer, "}");
            Serial.println(buffer);
putKinesis(GUID2,Org,Disp,Locn,Measure2,Units2,dtostrf(DHT.humidity, 5, 2, dtostrfbuffer));
            delay(500);
            // print string for light, separated by line for ease of reading
            memset(buffer, '\0', sizeof(buffer));
            strcat(buffer, "{");
            strcat(buffer, "\"guid\":\"");
            strcat(buffer, GUID3);
            strcat(buffer, "\",\"organization\":\"");
            strcat(buffer, Org);
            strcat(buffer, "\",\"timecreated\":\"");
            strcat(buffer, "timenow");
            strcat(buffer, "\",\"displayname\":\"");
            strcat(buffer, Disp);
            strcat(buffer, "\",\"location\":\"");
            strcat(buffer, Locn);
            strcat(buffer, "\",\"measurename\":\"");
            strcat(buffer, Measure3);
            strcat(buffer, "\",\"unitofmeasure\":\"");
            strcat(buffer, Units3);
            strcat(buffer, "\",\"value\":");
            strcat(buffer, dtostrf(lightsensorValue, 5, 3, dtostrfbuffer));
            strcat(buffer, "}");
            Serial.println(buffer);
putKinesis(GUID3,Org,Disp,Locn,Measure3,Units3,dtostrf(lightsensorValue, 5, 3, dtostrfbuffer));
            delay(500);
            // print string for motion, separated by line for ease of reading
            memset(buffer, '\0', sizeof(buffer));
            strcat(buffer, "{");
            strcat(buffer, "\"guid\":\"");
            strcat(buffer, GUID4);
            strcat(buffer, "\",\"organization\":\"");
            strcat(buffer, Org);
            strcat(buffer, "\",\"timecreated\":\"");
            strcat(buffer, "timenow");
            strcat(buffer, "\",\"displayname\":\"");
            strcat(buffer, Disp);
            strcat(buffer, "\",\"location\":\"");
            strcat(buffer, Locn);
            strcat(buffer, "\",\"measurename\":\"");
            strcat(buffer, Measure4);
            strcat(buffer, "\",\"unitofmeasure\":\"");
            strcat(buffer, Units4);
            strcat(buffer, "\",\"value\":");
            strcat(buffer, dtostrf(motionvalue, 3, 1, dtostrfbuffer));
            strcat(buffer, "}");
            Serial.println(buffer);
putKinesis(GUID4,Org,Disp,Locn,Measure4,Units4,dtostrf(motionvalue, 3, 1, dtostrfbuffer));
            delay(500);
	} else {
		Serial.println("Not publishing...");
	}


	delay(200);
}

char *dtostrf (double val, signed char width, unsigned char prec, char *sout) {
  char fmt[20];
  sprintf(fmt, "%%%d.%df", width, prec);	  sprintf(sout, fmt, val);
  return sout;
}

float get_light_level()
{

  float lightSensor = analogRead(LightSensorPin);
  lightSensor = 1 / lightSensor * 10;
  return (lightSensor);
}
void KinesisClient_Setup() {
	kClient.setHttpClient(&httpClient);
	kClient.setDateTimeProvider(&dateTimeProvider);
}
void putKinesis(String GUID, String Org, String Disp,String Locn, String Measure, String Units, String value) {
	

	char buffer[300];
	String dataSource;
	dataSource = String("{\"guid\":\"");
	dataSource += GUID;
	dataSource += String("\",\"organization\":\"");
	dataSource += Org;
	dataSource += String("\",\"timecreated\":\"");
	dataSource += dateTimeProvider.getDateTime();
	dataSource += String("\",\"displayname\":\"");
	dataSource += Disp;
	dataSource += String("\",\"location\":\"");
	dataSource += Locn;
	dataSource += String("\",\"measurename\":\"");
	dataSource += Measure;
	dataSource += String("\",\"unitofmeasure\":\"");
	dataSource += Units;
	dataSource += String("\",\"value\":");
	dataSource += value;
	dataSource += String("}");
	dataSource.toCharArray(buffer, 300);
	

	// simple blind putRecord, no way to read output of System call for now
	String output = kClient.putRecord(dataSource);
}















































































