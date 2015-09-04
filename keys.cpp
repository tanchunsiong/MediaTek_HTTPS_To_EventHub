// keys.cpp
#include "keys.h"

const char* awsKeyID = "AKIAJ7PddDHZKY2A"; // REPLACE with your access key id
const char* awsSecKey = "X0pgkwoHwNdd5BB7XF6FuEOqNuxyCeo"; // REPLACE with your secret access key


// Init and connect Edison wifi to local wlan
char* ssid = "SINGTEL-5880"; //  your network SSID (name)
char* pass = "removed";    // your network password (use for WPA, or use as key for WEP)

// Common AWS constants
const char* AWS_REGION = "";  
const char* AWS_ENDPOINT = "servicebus.windows.net";



/* Contants describing DynamoDB table and values being used. */
const char* HASH_KEY_NAME = "device_id";
const char* HASH_KEY_VALUE = "jin1234"; // REPLACE with your team or particpant name e.g Team38
const char* RANGE_KEY_NAME = "time";
const char* RANGE_KEY_VALUE = "1";
const char* TABLE_NAME = "m10new-DeviceDataTable-10WX560ZVUEIX"; //REPLACE with your DDB Table name e.g. hackday-2014-team38
const char* ATTRIBUTE_NAME = "device";
const char* ATTRIBUTE_VALUE = "mediatek";

/* Constants describing Kinesis stream */
const char* streamName = "m10new-DeviceStream-YQQ8HEN47JZF"; //REPLACE with your stream name e.g. hackday-2014-team38-TeamStream-1K5DAIU8GCRXY
const char* partitionKey = "partitionKey";




































































