# Intra-Vehicle Wireless Harness Communication
## Introduction:
Our graduation project is sponsored by **Dr. Mohamed Raid (EOIP company)** & **Swift Act**. This innovative project aims to address the complexity and limitations of traditional wired communication systems in vehicles by replacing them with wireless solutions using **Bluetooth Low Energy (BLE)** technology. We tested this approach across various simple vehicle systems, such as the dashboard screen, lighting, wipers, doors, and FOTA. Each of these systems implemented used the **Pico W module** and connected with each other using a BLE scatternet network.

## Problem Definition:
Automotive electrical systems currently rely heavily on physical wires, leading to complex and cumbersome wiring harnesses. As automakers add more features, the number of wires increases, making installation, maintenance, and troubleshooting challenging. Wireless communication can simplify these processes, reduce vehicle weight, enhance fuel efficiency, and improve system reliability and scalability.

## HW & SW:
## Hardware Components
* Raspberry Pi Pico W
* BeagleBone Black
* 5-inch HDMI display (800x480 pixels)
* PL2303 module (USB to TTL converter)
* Sensors and Actuators:
  - Liquid level sensor
  - DHT sensor (temperature and humidity)
  - Ultrasonic sensor
  - LED and push buttons
  - Servo motors
  - H-Bridge and DC motors
## Software Components
* IDE: Visual Studio Code (Pico SDK)
* “putty” or “Realterm” (serial console for UART)
* BeagleBone Operating System: Debian image
* QT Framework (for dashboard graphical interface)
* BLE Libraries (compatible with Raspberry Pi Pico W)
* FreeRTOS Libraries (for managing tasks on the Raspberry Pi Pico W)
* Documentation: Doxygen

## Content of project folders:
1. ECUs systems with BLE network
Contains the six systems we implemented to test this network. Each folder has the BLE code and the main code.
2. Linux and QT related (Dashboard)
Contains the dashboard QT application code and the code running at Beaglebone Black
3. PCB design
Contains 4 folders each has the Schematic files and PCB design 
## License
This is an open-source project. Feel free to use it, but please provide a reference to us when you do.

