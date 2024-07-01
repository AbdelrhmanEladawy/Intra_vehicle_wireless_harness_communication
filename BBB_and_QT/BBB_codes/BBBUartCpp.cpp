#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <jsoncpp/json/json.h>

#define UART_DEVICE "/dev/ttyS1"
#define JSON_FILE "/home/debian/jsonFileBBB.json"

using namespace std;

// Define message IDs
enum MessageID {
    SPEED_ID = 1,
    TEMPERATURE_ID = 2,
    HUMIDITY_ID = 3,
    DOOR_LIGHT_ID = 4,
    FRONT_LIGHT_ID = 5,
    WIBERS_ID = 6,
    FUEL_STATUS_ID = 7,
    WATER_STATUS_ID = 8,
    OIL_STATUS_ID = 9,
    RIGHT_ARROW_ID = 10,
    LEFT_ARROW_ID = 11
    // Add more message IDs as needed
};

// Struct to hold message information
struct Message {
    MessageID id;
    string data;
};

// Function to read from UART
Message readFromUART(int uart_fd) {
    char UART_buf[256];
    char data_buf[32];
    ssize_t len = read(uart_fd, UART_buf, sizeof(UART_buf));
    if (len > 0) {
        UART_buf[len-1] = '\0'; // Assuming the last character is a delimiter
        Message msg;
        // Assuming the format is "ID:DATA" 
        if (sscanf(UART_buf, "%d:%s", &msg.id, data_buf) == 2) {
            msg.data = string(data_buf);
            return msg;
        }
        else{
            cerr << "Error: Invalid message format received from UART - " << UART_buf << endl;
        }
    }
    else if (len < 0) {
        cerr << "Error: Unable to read from UART." << endl;
    }
    Message invalid_msg = {static_cast<MessageID>(-1), ""};
    return invalid_msg; // Invalid message
}

// Function to initialize UART
int initializeUART() {
    int uart_fd = open(UART_DEVICE, O_RDWR | O_NOCTTY);
    if (uart_fd == -1) {
        cerr << "Error: Unable to open UART." << endl;
        exit(1);
    }
    else{
        cout<<"port : "<<uart_fd<<" opend\n";
    }

    struct termios options;
    tcgetattr(uart_fd, &options);
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart_fd, TCIFLUSH);
    tcsetattr(uart_fd, TCSANOW, &options);

    return uart_fd;
}

// Function to update JSON file
void updateJSON(const Message& msg) {
    Json::Value root;
    ifstream json_file(JSON_FILE);
    if (json_file.good()) {
        json_file >> root;
    }
    json_file.close();

    // Update JSON based on message ID
    switch (msg.id) {
        case SPEED_ID:
            if( (stoi(msg.data) >= 0) && (stoi(msg.data) <= 400) )
                root["speed"] = msg.data;
            else{
                cout<<"Invaild speed Data !\n";
                return;
                }
            break;
        case TEMPERATURE_ID:
            if( (stoi(msg.data) >= -100) && (stoi(msg.data) <= 200) )
                root["temperature"] = msg.data;
            else{
                cout<<"Invaild temptrature Data !\n";
                return;
                }
            break;
        case HUMIDITY_ID: 
            if( (stoi(msg.data) >= 0) && (stoi(msg.data) <= 100) )
                root["humidity"] = msg.data;
            else{
                cout<<"Invaild humidity Data !\n";
                return;
                }
            break;
        case DOOR_LIGHT_ID: 
            if(msg.data == "1")
                root["door_light"] = true;
            else if(msg.data == "0")
                root["door_light"] = false;
            else{
                cout<<"Invaild door light Data !\n";
                return;
            }
            break;
        case FRONT_LIGHT_ID: 
            if(msg.data == "1")
                root["front_light"] = true;
            else if(msg.data == "0")
                root["front_light"] = false;
            else{
                cout<<"Invaild front light Data !\n";
                return;
            }
            break;
        case WIBERS_ID: 
            if(msg.data == "1")
                root["wiber"] = true;
            else if(msg.data == "0")
                root["wiber"] = false;
            else{
                cout<<"Invaild wibers Data !\n";
                return;
            }
            break;
        case FUEL_STATUS_ID: 
            if(msg.data == "1")
                root["fuel_states"] = true;
            else if(msg.data == "0")
                root["fuel_states"] = false;
            else{
                cout<<"Invaild fuel status Data !\n";
                return;
            }
            break;
        case WATER_STATUS_ID: 
            if(msg.data == "1")
                root["water_states"] = true;
            else if(msg.data == "0")
                root["water_states"] = false;
            else{
                cout<<"Invaild water status Data !\n";
                return;
            }
            break;
        case OIL_STATUS_ID: 
            if(msg.data == "1")
                root["oil_states"] = true;
            else if(msg.data == "0")
                root["oil_states"] = false;
            else{
                cout<<"Invaild oil status Data !\n";
                return;
            }
            break;
        case RIGHT_ARROW_ID: 
            if(msg.data == "1")
                root["right_arrow_state"] = true;
            else if(msg.data == "0")
                root["right_arrow_state"] = false;
            else{
                cout<<"Invaild right arrow Data !\n";
                return;
            }
            break;
        case LEFT_ARROW_ID: 
            if(msg.data == "1")
                root["left_arrow_state"] = true;
            else if(msg.data == "0")
                root["left_arrow_state"] = false;
            else{
                cout<<"Invaild left arrow Data !\n";
                return;
            }
            break;
        // Handle additional message IDs here
        default:
            cout << "NOT Vaild ID\n";
            return;
    }

    ofstream outfile(JSON_FILE);
    if (!outfile.is_open()) {
        cerr << "Error: Unable to open JSON file for writing." << endl;
        exit(1);
    }
    outfile << root;
    outfile.close();
}

int main() {
    int uart_fd = initializeUART();
    while (true) {
        Message msg = readFromUART(uart_fd);
        if (msg.id != -1) {
            cout << "Received data from UART - ID: " << msg.id << ", Data: " << msg.data << endl;
            updateJSON(msg);
        }
        usleep(500); // Sleep for 0.05 second
    }

    close(uart_fd);
    return 0;
}
