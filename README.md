# Litterbot
Class Project for ROB-GY 6103 Advanced Mechatronics 

## Abstract
The project's goal is to create an autonomous robot that cleans trash in cities that is tailored to its needs. This mobile robot, which combines Arduino and Raspberry Pi, makes use of an Ultrasonic sensor that was moved from the Propeller platform. With the help of the Raspberry Pi, the robot can be wirelessly controlled by an operator. Its capacity to automatically identify and categorize waste utilizing an ultrasonic sensor system and a camera system is a crucial feature, since it allows a robotic arm to be autonomously activated for garbage collection. Efficient navigation and trash handling in intricate urban environments are made possible by the smooth data flow and control that serial connectivity between Arduino and Raspberry Pi provides.

## 1. Introduction
In the pursuit of innovative urban waste management solutions, our project introduces a semi-autonomous litter-cleaning robot. This robot integrates a Raspberry Pi and Arduino, utilizing their computational and control capabilities to navigate and interact within urban environments effectively. Central to its operation, the PiCamera module captures images of objects within range of the robotic arm, which is processed using the MobileNetV3 model to identify and classify objects as trash. Coupled with this advanced image recognition is the use of an ultrasonic sensor mounted on the Arduino, enabling the robot to detect objects within a range of 20 cm and trigger image capture. This sensor data is communicated to the Raspberry Pi via a
robust serial connection, allowing for sophisticated decision-making processes.

## 2. Objectives
Our primary objectives as set forth by our project proposal were:

- Integrate the Arduino and Raspberry Pi onto our mobile robot platform.
- Implement full wireless control and communication of the robot.
- Autonomously detect trash and trigger the deployment of the robot arm for trash pickup using the ultrasonic sensor.

## 3. Methodology
### 3.1 Main Features
- Wireless Operation: Enable users to wirelessly command the robot via the Raspberry Pi for enhanced maneuverability and control.
- Efficient Communication: Establish robust serial communication between Raspberry Pi and Arduino to transmit object detection notifications and classifications.
- Sensor Optimization: Utilize ultrasonic sensors to detect objects within a 20 cm range regardless of orientation.
- Object Recognition: Utilize the MobileNet model to reliably identify objects
### 3.2 Circuit Diagram
![image](https://github.com/RiVer2000/litter-bot/assets/64482413/2d5759d4-c49c-41ca-b5eb-8b1b084cc0d3)

### 3.3 Object Detection and Recognition
The robot is programmed to specifically recognize items commonly categorized as litter, such as paper cups. Once an object is identified as trash by the PiCam, i.e. the paper cup, and is within a
20 cm range detected by an ultrasonic sensor, the system triggers the robotic arm to collect the
item and deposit it into an onboard bin. Conversely, objects not recognized as trash are moved
aside, allowing the robot to effectively manage waste by segregating and disposing of litter
appropriately in urban environments. This integration of machine learning and robotics
technology streamlines waste management processes, enhancing the robot's utility and efficiency.
The MobileNetV2 model for real-time object detection was utilized via a Raspberry Pi equipped
with a PiCamera. This advanced neural network is adept at identifying various objects within
visual frames, allowing our autonomous litter-cleaning robot to detect and classify items
effectively. By processing images captured when triggered by the ultrasonic sensor, the system
can identify specific waste items such as paper cups.
The software at a high level performs the following tasks. The RPi receives keyboard input
through ssh via WiFi connection and forwards them directly to the Arduino. This allows the
users to drive the robot and control each joint of the robotic arm and command it into some
pre-saved positions such as “stowed” or “deployed”.
The trash detection operates in a functional loop between the Arduino and Rpi. The Arduino first
detects an object within range. In this case, we’ve defined that range to be 20 cm. It then stops
reading any user input for driving or robotic arm control and sends a request to the RPi to capture
an image and identify the object that was detected. The RPi will process the image and run it
through the MobileNet model to identify the type of object that was detected. If the item is
suitable for collection and classified as “trash”, a flag is sent to the Arduino to perform a series
of actions to pick up the object and place it in the on-board bin. If the item is not classified as
“trash”, a flag is sent to the Arduino to move the object to the side.
## Results
[![Watch the video](https://github.com/user-attachments/assets/f9cbbf7f-910a-40a0-9e87-45c634838020)
](https://github.com/RiVer2000/litter-bot/blob/main/litter_bot_demo_video.mp4)


