# ESP32CAM-RTSP-SERVER
an ESP32 CAM based RTSP Server that utilizes CircuitRocks' code for RTSP video streaming.

Link to the CircuitRocks article: https://learn.circuit.rocks/esp32-cam-with-rtsp-video-streaming

# Setup
The ESP32 CAM is connected to a SR-501 motion sensor, by default Pin no. 12 of the ESP32 is connected to the output of the sensor. To change this pin number, edit the rtsp.cpp file and change the SensorPin variable.
A 5V power supply must be connected to the sensor as well. These are the only components required for the project.

After the ESP32 CAM has been connected to the SR-501 sensor, you can upload the arduino code into the module. Make sure that the ESP32 is in download mode, that the libraries are included, and that no files are removed from the src folder. Be sure to change the wifi_keys.h file to include your SSID and password.

# How to Use
Once the code has been uploaded on the ESP32, it will try to connect to the wifi network. If it successfully connects, take the RTSP stream link and write it in the serverconfig.txt file in the Recorder folder. Run the python code inside of that folder and it should begin to grab the stream from the RTSP server. If the ESP32 detects motion through the SR-501 sensor, it will start streaming for 30 seconds and an additional 30 seconds for every time it detects motion again.

Once the stream is done uploading, the ESP32 will close the stream and the python program will save the video as a file with the time of recording as the name (In the format Year-Month-Day_Hour-Minute-Second).

# Issues
The ESP32 sensor needs to be adjusted before it is used or else the stream will never pause.

There should be a version of the code without the sensor, but that's a future task.
