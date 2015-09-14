/*
 * AWSClient.h
 *
 *  Base classes for services to create an HTTP request.
 *
 *  Created on: Jul 8, 2014
 *      Author: hoffmaj
 */

#ifndef AWSCLIENT_H_
#define AWSCLIENT_H_

#include "DeviceIndependentInterfaces.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <Arduino.h>

/* Total number of headers. */
static const int HEADER_COUNT = 5;


/* Base class for an AWS Service Client. Creates http and https request in raw
 * http format or as a curl command. */
class AWSClient {
  
  
    /* Number of headers created. */
    int headersCreated;
    /* Array of the created http headers. */
    char* headers[HEADER_COUNT];
    /* Array of string lengths of the headers in the "headers" array. */
    int headerLens[HEADER_COUNT];
    /* The payload of the httprequest to be created */
    String payload;

    /* Add the headers that will be signed to the headers array. Called before
     * createStringToSign. */
    void initSignedHeaders();

	/* Add the headers that will not be signed to the headers array. Called
	* after createSignature. */
	void initUnsignedHeaders();
    /* Contains all of the work to be done before headersToRequest or
     * headersToCurlRequest are called. Takes the payload to be sent and the
     * GMT date in yyyyMMddHHmmss format. */
    void createRequestInit(String &reqPayload);
    /* Clean up after headersToRequest or headersToCurlRequest are called. */
    void createRequestCleanup();
    /* Using the headers array, create a raw http request. */
    char* headersToRequest(void);
   

protected:
    /* Used to keep track of time. */
    IDateTimeProvider* dateTimeProvider;
    /* Used to send http to the server. */
    IHttpClient* httpClient;
	/* Content type of payload, eg. "application/x-amz-json-1.1". */
	const char* contentType;
    /* true if https is to be used, false if http is to be used. */
    bool httpS;
 
    /* Creates a raw http request, given the payload and current GMT date in
     * yyyyMMddHHmmss format. Should be exposed to user by extending class.
     * Returns 0 if client is unititialized. */
    char* createRequest(String &payload);
  
    /* Sends http data. Returns http response, or null on error. */
    char* sendData(const char* data);
    /* Empty constructor. Must also be initialized with init. */
    AWSClient();

public:
    /* Setters for values used by createRequest and createCurlRequest. Must
     * be set or create[Curl]Request will return null. */
  
    void setHttpClient(IHttpClient* httpClient);
    void setDateTimeProvider(IDateTimeProvider* dateTimeProvider);
    ~AWSClient(void);
};

#endif /* AWSCLIENT_H_ */
