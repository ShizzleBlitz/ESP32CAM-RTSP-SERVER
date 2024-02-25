import cv2
from datetime import datetime
import time 
  

f = open("serverconfig.txt", "r")
stream = f.read()

while True:
    video = cv2.VideoCapture(stream)
    filename = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
   
    #introduce delay for 1 second until stream is captured again
    if (video.isOpened() == False):  
        print("Error reading video file")
        continue

    #converting resolution to integer
    frame_width = int(video.get(3)) 
    frame_height = int(video.get(4)) 
   
    size = (frame_width, frame_height) 
    print(filename + '.avi')
    result = cv2.VideoWriter(filename + '.avi',  
                         cv2.VideoWriter_fourcc(*'MJPG'), 
                         10, size) 
    
    while(True): 
        ret, frame = video.read() 
  
        if ret == True:  
            result.write(frame) 
            cv2.imshow('Frame', frame) 
  
        # Break the loop 
        else: 
            break
  
    # When everything done, release  
    # the video capture and video  
    # write objects 
    video.release() 
    result.release() 
    
    # Closes all the frames 
    cv2.destroyAllWindows() 
   
    print("The video was successfully saved")