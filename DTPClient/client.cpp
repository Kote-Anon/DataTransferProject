#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "dataSaver.cpp" // Include dataSaver.cpp to use its functions
#include "fileTransfer.cpp" // Include fileTransfer.cpp to use its functions

int main(int argc, char *argv[]) {
    // Call the function to save system information to CSV
    saveSystemInfoToCSV();

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    const char* FILENAME = argv[1];

    // Read settings from file
    std::string ip;
    int port = -1;
    int buffer_size = -1;
    std::ifstream settingsFile("DTPCSettings.txt");
    if (settingsFile.is_open()) {
        std::string line;
        while (std::getline(settingsFile, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, '=') && std::getline(iss, value)) {
                if (key == "ip") {
                    ip = value;
                } else if (key == "port") {
                    port = std::stoi(value);
                } else if (key == "buffer_size") {
                    buffer_size = std::stoi(value);
                }
            }
        }
        settingsFile.close();
    }

    // Check if required settings are present
    if (ip.empty() || port == -1 || buffer_size == -1) {
        std::cerr << "Error: Incomplete settings in DTPCSettings.txt" << std::endl;
        return 1;
    }

    // Send the file to the server
    if (!sendFile(FILENAME, ip.c_str(), port)) {
        std::cerr << "Failed to send file." << std::endl;
        return 1;
    }

    return 0;
}