// keys.cpp
#include "keys.h"

const char* awsKeyID = "AKIAJ7PddDHZKY2A"; // REPLACE with your access key id
const char* awsSecKey = "X0pgkwoHwNdd5BB7XF6FuEOqNuxyCeo"; // REPLACE with your secret access key
const char* SASString = "SharedAccessSignature sr=https%3a%2f%2fcspi2-ns.servicebus.windows.net%2fehdevices%2fpublishers%2fmediateksender%2fmessages&sig=ast4SkZqdtP5GN7nOY6pGYerbWCbaOuc2SZ0ig3w3Xw%3d&se=1754891846&skn=mediateksender";
const char* eventhubname="mediateksender";
const char* sendername="ehdevices";


// Init and connect Edison wifi to local wlan
char* ssid = "SINGTEL-5880"; //  your network SSID (name)
char* pass = "42evrxyd";    // your network password (use for WPA, or use as key for WEP)

// Common AWS constants
	//dreamtcs
    const char* EH_NAMESPACE = "cspi2-ns";
	//this would be eventhub namespace
	const char* AWS_REGION = "servicebus";  
	//dreamtcs
	//this would be eventhub server
	const char* AWS_ENDPOINT = ".windows.net";

	const char* MESSAGES = "messages";
	 const char* PUBLISHERS="publishers";


//dreamtcs try to remove this
/* Constants describing Kinesis stream */
const char* streamName = "m10new-DeviceStream-YQQ8HEN47JZF"; //REPLACE with your stream name e.g. hackday-2014-team38-TeamStream-1K5DAIU8GCRXY
const char* partitionKey = "partitionKey";



































































