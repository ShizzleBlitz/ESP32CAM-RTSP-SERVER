#include "main.h"
#ifdef ENABLE_RTSPSERVER

// Use this URL to connect the RTSP stream, replace the IP address with the address of your device
// rtsp://192.168.0.109:8554/mjpeg/1

/** Forward dedclaration of the task handling RTSP */
void rtspTask(void *pvParameters);

/** Task handle of the RTSP task */
TaskHandle_t rtspTaskHandler;

/** WiFi server for RTSP */
WiFiServer rtspServer(8554);

/** Stream for the camera video */
CStreamer *streamer = NULL;
/** Session to handle the RTSP communication */
CRtspSession *session = NULL;
/** Client to handle the RTSP connection */
WiFiClient rtspClient;
/** Flag from main loop to stop the RTSP server */
boolean stopRTSPtask = false;
//Pin where the motion sensor is connected
int SensorPin = 12;
//Time in milliseconds for how long it will record after detecting motion
int recordTime = 30000;

/**
 * Starts the task that handles RTSP streaming
 */
void initRTSP(void)
{
  pinMode(SensorPin,INPUT);
	// Create the task for the RTSP server
	xTaskCreate(rtspTask, "RTSP", 4096, NULL, 1, &rtspTaskHandler);

	// Check the results
	if (rtspTaskHandler == NULL)
	{
		Serial.println("Create RTSP task failed");
	}
	else
	{
		Serial.println("RTSP task up and running");
	}
}

void rtspTask(void *pvParameters)
{
	uint32_t msecPerFrame = 100; //changing how many seconds per frame from 50 to 200
	static uint32_t lastimage = millis();
  static uint32_t starttime = 0;

  // rtspServer.setNoDelay(true);
	rtspServer.setTimeout(1);
	rtspServer.begin();

	while (1)
	{
    //Serial.println(digitalRead(SensorPin));
		// If we have an active client connection, just service that until gone
		if (session)
		{
      if (digitalRead(SensorPin) == 1)
        starttime = millis();

			session->handleRequests(0);
      // we don't use a timeout here,
			// instead we send only if we have new enough frames

			uint32_t now = millis();
			if (now > lastimage + msecPerFrame || now < lastimage)
			{ // handle clock rollover
				session->broadcastCurrentFrame(now);
				lastimage = now;
			}

      if (lastimage - starttime > recordTime)
      {
        Serial.println("Shut down RTSP server because OTA starts");
				delete session;
				delete streamer;
				session = NULL;
				streamer = NULL;
      }

			// Handle disconnection from RTSP client
			else if (session->m_stopped)
			{
				Serial.println("RTSP client closed connection");
				delete session;
				delete streamer;
				session = NULL;
				streamer = NULL;
			}
		}
		else if (session == NULL && digitalRead(SensorPin) == 1)
		{
      
      rtspClient = rtspServer.accept();
      
			// Handle connection request from RTSP client
			if (rtspClient)
			{
				Serial.println("RTSP client started connection");
				streamer = new OV2640Streamer(&rtspClient, cam); // our streamer for UDP/TCP based RTP transport

				session = new CRtspSession(&rtspClient, streamer); // our threads RTSP session and state
        starttime = millis();
			}
		}
		delay(10);
	}
}
#endif
