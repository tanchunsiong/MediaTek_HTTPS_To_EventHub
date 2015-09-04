
#include <LWiFi.h>
#include <LWiFiClient.h>
#include <Wire.h>
#include <LDateTime.h>

#include "MtkAWSImplementations.h"
#include "AWSFoundationalTypes.h"
#include "keys.h"
#include "AWShelperFunctions.h"

#include <dht11.h>
#include <stdlib.h>
#define dht_dpin 1 //no ; here. Set equal to channel sensor is on
#include <stdio.h>



MtkHttpClient c;
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
	Serial.begin(9600);
       
       
        Serial.println("Begin Setup..");
        
        // Connect to WiFi (function loops until successful connection is made)
	    Mtk_Wifi_Setup(ssid, pass);
        printWifiStatus();
        Serial.println("Wi-Fi connected");
        

        Serial.println("Sensors connected");
        //dreamtcs to change
        Serial.println("Client connected");
	KinesisClient_Setup();
	Serial.println("Setup complete! Looping main program");
	Serial.println("Initial mode: KINESIS");      
        
}

unsigned long currentTime = 0;
unsigned long LastPostTime = 0;
enum {
	POSTING_PERIOD_MS = 500
};




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
	    putKinesis(buffer);
            //char* server="cspi2-ns.servicebus.windows.net";
            //char* data ="POST https://cspi2-ns.servicebus.windows.net/ehdevices/publishers/mediateksender/messages HTTP/1.1 \nAuthorization: SharedAccessSignature sr=https%3a%2f%2fcspi2-ns.servicebus.windows.net%2fehdevices%2fpublishers%2fmediateksender%2fmessages&sig=ast4SkZqdtP5GN7nOY6pGYerbWCbaOuc2SZ0ig3w3Xw%3d&se=1754891846&skn=mediateksender \nContent-Type: application/atom+xml;type=entry;charset=utf-8 \nHost: cspi2-ns.servicebus.windows.net \nContent-Length: 53 \n\n{ \"DeviceId\":\"dev-01\", \"Temperature\":\"37.0\" }";
            //char* response =httpClient->send(data, server, 443);
            
            //char* server="cspi2-ns.servicebus.windows.net";
            //char* data ="GET https://www.facebook.com HTTP/1.1 \nHost: www.facebook.com \nConnection: close";
            //char* response =c.send(data, server, 443);


			
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
            strcat(buffer, dtostrf(DHT.humidity, 5, 2, dtostrfbuffer));
            strcat(buffer, "}");
            Serial.println(buffer);
            putKinesis(buffer);
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
            putKinesis(buffer);
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
            putKinesis(buffer);
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
































































