# Smart_Bin
Developed a prototype for automated bin using IoT sensors such as PIR Motion Sensor, Sharp IR Analog Sensor, Servo Motors, HC-SR04 Distance 
Sensor.
Automatically opens up the lid once a person stands in front and keeps the lid opens untill person moves away from the bin. Also notifies the particular department if the bin is full and refrains itself from opening the lid. Gives timely status of bin. 
For sending updates Telegram Application has been used which is integrated with NodeMcu using  Telegram API. 
Servo Motors are used for opening of lid and HC-SR04 Distance Sensor is placed inside the bin to know status of bin. 
Sharp IR Analog sensor is used to detect the presence of person standing in front. In order to optimize the power consumption PIR Motion sensor has been placed outside which make sures that Analog Sensor is working only when movement is detected.
