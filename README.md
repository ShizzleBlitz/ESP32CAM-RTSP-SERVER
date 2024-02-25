# ESP32CAM-RTSP-SERVER
an ESP32 CAM based RTSP Server that utilizes CircuitRocks' code for RTSP video streaming.

Link to the CircuitRocks article: https://learn.circuit.rocks/esp32-cam-with-rtsp-video-streaming

# Setup
The ESP32 CAM is connected to a SR-501 motion sensor, by default Pin no. 12 of the ESP32 is connected to the output of the sensor. To change this pin number, edit the rtsp.cpp file and change the SensorPin variable.
A 5V power supply must be connected to the sensor as well. These are the only components required for the project.

After the ESP32 CAM has been connected to the SR-501 sensor, you can upload the arduino code into the module. Make sure that the ESP32 is in download mode, that the libraries are included, and that all of the C++ files are present in the same folder as the Arduino source file.

# How to Use
Once the code has been uploaded on the 
