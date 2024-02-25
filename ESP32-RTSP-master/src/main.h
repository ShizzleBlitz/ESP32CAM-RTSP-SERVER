#include <Arduino.h>

// WiFi stuff
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>

// Camera stuff
#include "OV2640.h"
#include "OV2640Streamer.h"
#include "CRtspSession.h"

#define ENABLE_RTSPSERVER

// Camera class
extern OV2640 cam;

// RTSP stuff
void initRTSP(void);
void stopRTSP(void);
