# QT Project
The project aims to simulate a dashboard for a car, reading data such as speed, temperature, and fuel state from a JSON file. The project uses the Qt framework and is structured to be modular and easy to understand.

Grateful thanks to [Adesh Singh](https://github.com/cppqtdev) [and Design League](https://youtu.be/UwONyUrIOe8?si=SERkR77MeYzPLczu) for providing an example of how the dashboard should look.

## File Structure
* **Car_1.pro:** Qt project file containing build configurations.
* **main.qml:** The main QML file, which sets up the application interface.
* **RadialBar.qml:** Custom QML component for displaying radial progress indicators.
* **get_data/jsonreader.h:** Header file for the jsonReader C++ class.
* **get_data/jsonreader.cpp:** Source file for the jsonReader C++ class.
* **main.cpp:** Main entry point of the application.
* **qml.qrc:** Resource file listing QML files used in the project.

## Prerequisites
To build and run this project, you need:
* Qt 5.15 or later
* C++11 compatible compiler and cross compile for Beaglebone
* Qt Creator
* QT Cross-compiler for ARM architecture



## How to Build
1. Set Up Cross-Compiler
Install the necessary cross-compiler for ARM architecture.
2. Set Up Qt for Cross-Compilation
Install Qt for cross-compilation and configure the environment for BeagleBone Black.
3. Clone the Repository
    ```bash
    git clone <repository-url>
    cd <repository-name>
    ```
4. Open the Project in Qt Creator
    Launch Qt Creator and open **Car_1.pro**.
5. Configure the Build Kit
Set up a build kit in Qt Creator with the cross-compiler for BeagleBone Black.
6. Build the Project
Use the Qt Creator build button to compile the project.




## How to run
1. Transfer the Compiled File to BeagleBone
Use sftp, scp, or any other file transfer method to transfer the built executable to your BeagleBone Black.
    ```bash
    scp path/to/Car_1 root@beaglebone:/home/debian/
    ```
and don't forget to change "path/to/Car_1"

2. Run the Application on BeagleBone Black
SSH into your BeagleBone Black or use PuTTY, and run the application.
    ```bash
    ssh debian@192.168.7.2
    cd /home/debian
    ./Car_1
    ```

## Detailed Description of Components

### main.qml
We can divide the QML file or what is displayed on the screen as follows:
* **Data Update:** Handles periodic data updates from the JSON file.
* **Dashboard and Background:** Represents the main dashboard layout and background image.
* **Top Bar:** Displays the top bar with current time, date, and weather icon.
* **Bottom Bar:** Displays the bottom bar, typically for additional controls or status indicators.
* **Left Icons:** Contains the icons displayed on the left side of the dashboard.
* **Right Icons:** Contains the icons displayed on the right side of the dashboard.
* **Speed Label:** Displays the current speed of the car.
* **Left and Right Arrow Icons:** Displays the left and right arrow icons for turn signals or indicators.
* **Radial Bar:** Represents a radial progress bar, such as for temperature or fuel.


### Update data "jsonreader.cpp" file
The `jsonreader.cpp` is just class created to access the JSON file and read the data to store it into variable throw function called `readAllData()`. The update process done ever interval of time in QML file due to timer at “Data Update” section, this timer called the function `readAllData()` and change the configuration of other section in the QML wither getter functions, which at the end will affect what showing at screen.
The `jsonreader.cpp` class is created to access the JSON file and read the data to store it into a variable through a function called `readAllData()`.The update process is done at regular intervals in the QML file due to a timer in the "Data Update" section. This timer calls the function `readAllData()` and updates the configuration of other sections in the QML with getter functions, which ultimately affect what is shown on the screen.

## Realted Links
* [Qt 6 With C++ playlist](https://youtube.com/playlist?list=PLUbFnGajtZlXbrbdlraCe3LMC_YH5abao&si=KTFdU7jtivhsDY6Y)
* [QT QML playlist](https://youtube.com/playlist?list=PL5DvWI_sM78qIMyTQEaa1KSX_6hIqUwV3&si=fwd3TdM3rp2vm0z3)
* [PyQt5 GUI playlist](https://youtube.com/playlist?list=PLCC34OHNcOtpmCA8s_dpPMvQLyHbvxocY&si=m0azBL7yHdBj4MPk)
* [How To Write and Read JSON File by Qt](https://www.weiy.city/2020/08/how-to-write-and-read-json-file-by-qt/)