# BeagleBone Black (GUI system)
The dashboard is a component of our BLE network system that receives data for GUI visualization. Examples of the data received include speed, light status, fuel level, temperature, etc. This data is sent to the Pico W via BLE (Bluetooth Low Energy) and then transmitted to the BeagleBone Black through UART (Universal Asynchronous Receiver-Transmitter).

## Flow of data from network to screen

As the data is received by the Pico W via BLE, it is stored in a queue variable buffered in the Pico W. This queue is then read, and the data is updated in a local variable stored in the Pico W. This variable is then sent to the BeagleBone Black via the UART port. At the BeagleBone Black, the operating system stores the received data from UART in a JSON file. The QT application reads this JSON file and updates the widget or the picture shown on the screen via HDMI.


## installation steps 
Note: It is recommended to use a Linux OS for BeagleBone installation steps.
1. Download Debian image for BeagleBone Black from [here](https://www.beagleboard.org/distros) (the "AM335x 11.7 2023-09-02 4GB microSD IoT" image is recommended).
2. Install SD card read and using [Balena Etcher](https://etcher.balena.io/) program, flash the image into SD card
3. Insert the SD card into the BeagleBone Black, press the boot button, and then connect it to power.
4. Connect the serial port on the BeagleBone Black as shown in the following figure, and then connect it to your PC or laptop.
 ![BeagleBone Black TTL connections](https://miro.medium.com/v2/resize:fit:1400/1*AU51n75Ls0JwfPeYMD6sIQ.png)
 
5. On your PC, open [Putty](https://www.putty.org/) or “[SSH / Remote access](https://subscription.packtpub.com/book/iot-and-hardware/9781783982929/1/ch01lvl1sec18/ssh-remote-access)”
6. After a while, the BeagleBone will power up and prompt you to enter a username and password. Use "debian" as the username and "temppwd" as the password
7. If need to connect to wifi via usb, follow this [link](https://opencoursehub.cs.sfu.ca/bfraser/grav-cms/cmpt433/guides/files/Networking.pdf) for linux, or this [link](https://ofitselfso.com/BeagleNotes/HowToConnectBeagleboneBlackToTheInternetViaUSB.php) for windows (linux is more recommended)
8. To install a visual desktop environment on the BeagleBone, you can install [LXDE](https://wiki.debian.org/LXDE)
9. On your PC, install [QT creator](https://www.qt.io/product/development-tools) and the cross-compiler for BeagleBone. Also, install any [necessary libraries](https://wiki.qt.io/BeagleBone_Black_Beginners_Guide) on the BeagleBone.
10. If you need to send data or files to the BeagleBone or retrieve them, you can use the command sftp debian@192.168.7.2 in the terminal.
11. If you going to use python at BeagleBone, make sure to install [Adafruit-BBIO](https://pypi.org/project/Adafruit-BBIO/) library 
 

## Realted Links
- [Setup Beaglebone Board](https://embetronicx.com/tutorials/linux/device-drivers/setup-beaglebone-board-linux-device-driver-tutorial/#Enable_the_ethernet_via_USB0)
- [Connect beaglebone Black to internet via usb](https://opencoursehub.cs.sfu.ca/bfraser/grav-cms/cmpt433/guides/files/Networking.pdf)
- [SSH to BeagleBone Black over USB](https://cdn-learn.adafruit.com/downloads/pdf/ssh-to-beaglebone-black-over-usb.pdf)
- [How to Transfer Files Between BeagleBoneBlack and PC](https://youtu.be/u_ohQMGV4Ug?si=UQoRj3uf5un7C6HP)
- [Beaglebone Black LESSONS](https://youtube.com/playlist?list=PLGs0VKk2DiYyThNvj6VyDFmOnQ8ncXk8b&si=f7osz5iGdVzQglQV)
- [Install Qt Creator on Linux](https://web.stanford.edu/dept/cs_edu/resources/qt/install-linux)
- [Crosscompile Qt 5.2.1 for the Beaglebone Black](https://vt-tech.eu/en/articles/programming/2-crosscompile-qt-5-2-1-for-the-beaglebone-black)
- [QT, BeagleBone Black Beginners Guide](https://wiki.qt.io/BeagleBone_Black_Beginners_Guide)
