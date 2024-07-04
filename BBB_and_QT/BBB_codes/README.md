# Beagle Bone Black UART and JSON codes
This project involves reading data from UART and updating a JSON file accordingly. The program is implemented in C++ and designed to run on a BeagleBone Black.

## files descreption 
* BBBUartCpp.cpp : C++ code to read from the UART port and update JSON file data.
* pyBBBTest.py : Tests the Adafruit_BBIO library in Python to ensure it runs correctly.
* pyBBBUart.py : Opens the UART port and tests the data received through UART.
* pyJSONTest.py : Tests the JSON library in Python.

##  BBBUartCpp.cpp
### prerequisite
Before running the program, ensure that the following dependencies are installed on your BeagleBone Black:
1. **gcc and g++**: C and C++ compilers.
   ```bash
   sudo apt-get update
   sudo apt-get install build-essential
   ```
2. **libjsoncpp:** Library for JSON manipulation in C++ 
   ```bash
   sudo apt-get install libjsoncpp-dev
   ```

also, Make sure the JSON file path `/home/debian/jsonFileBBB.json` exists and is writable. If it doesn't, create an empty file with the correct permissions:
```bash
sudo touch /home/debian/jsonFileBBB.json
sudo chmod 666 /home/debian/jsonFileBBB.json
```

On the BeagleBone Black, UART1 is typically available at `/dev/ttyO1`. so, if you use another UAT make sure to change it at the code.

### Compiling the Program
Compile the code using the following command
```bash
g++ -o BBBUartCpp BBBUartCpp.cpp -ljsoncpp
```

### running the program
``` bash
sudo ./BBBUartCpp
```


## pyBBBTest.py
This script tests the Adafruit_BBIO library by toggling a GPIO pin on the BeagleBone Black. The script will turn an output pin on and off five times, with each state lasting three seconds.
### prerequisite
**Adafruit_BBIO:** A library for controlling GPIO pins on the BeagleBone Black.
```bash
sudo apt-get update
sudo apt-get install python3-pip
sudo pip3 install Adafruit_BBIO
```

### Running the Program
```bash
python3 pyBBBTest.py
```

## pyBBBUart.py
This script opens a UART port on the BeagleBone Black and continuously sends and receives data through it. The script sends "Hello World!" to the UART port and prints any data received from the port.

### prerequisite
1. **Adafruit_BBIO:** A library for controlling UART on the BeagleBone Black.
    ```bash
    sudo apt-get update
    sudo apt-get install python3-pip
    sudo pip3 install Adafruit_BBIO
    ```
2. **pySerial:** A library for serial communication in Python
    ```bash
    sudo pip3 install pyserial
    ```

### Running the Program
```bash
python3 pyBBBUart.py
```

## pyJSONTest.py
This script tests the JSON library by reading, modifying, and writing a JSON file. It reads the JSON file located at /home/debian/jsonFileBBB.json, updates for example the speed and fuel states, and writes the changes back to the file.
### Running the Program
```bash
python3 pyJSONTest.py
```