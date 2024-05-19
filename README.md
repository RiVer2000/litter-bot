# Litterbot
Class Project for ROB-GY 6103 Advanced Mechatronics 

## Abstract
The project's goal is to create an autonomous robot that cleans trash in cities that is tailored to its needs. This mobile robot, which combines Arduino and Raspberry Pi, makes use of an Ultrasonic sensor that was moved from the Propeller platform. With the help of the Raspberry Pi, the robot can be wirelessly controlled by an operator. Its capacity to automatically identify and categorize waste utilizing an ultrasonic sensor system and a camera system is a crucial feature, since it allows a robotic arm to be autonomously activated for garbage collection. Efficient navigation and trash handling in intricate urban environments are made possible by the smooth data flow and control that serial connectivity between Arduino and Raspberry Pi provides.

## 1. Introduction
In the pursuit of innovative urban waste management solutions, our project introduces a semi-autonomous litter-cleaning robot. This robot integrates a Raspberry Pi and Arduino, utilizing their computational and control capabilities to navigate and interact within urban environments effectively. Central to its operation, the PiCamera module captures images of objects within range of the robotic arm, which is processed using the MobileNetV3 model to identify and classify objects as trash. Coupled with this advanced image recognition is the use of an ultrasonic sensor mounted on the Arduino, enabling the robot to detect objects within a range of 20 cm and trigger image capture. This sensor data is communicated to the Raspberry Pi via a
robust serial connection, allowing for sophisticated decision-making processes.
