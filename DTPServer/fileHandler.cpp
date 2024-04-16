// fileHandler.cpp

#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring> // for strcmp
#include <ctime> // for timestamp
#include <sys/stat.h>
#include <filesystem> // for filesystem operations

#define PORT 8080
#define BUFFER_SIZE 1024

std::string generateFilename() {
    // Create ReceivedFiles folder if it doesn't exist
    const char* folder_name = "ReceivedFiles";
    if (mkdir(folder_name, 0777) == -1) {
        // If folder already exists or creation fails for some reason, continue
        if (errno != EEXIST) {
            perror("mkdir");
            exit(EXIT_FAILURE);
        }
    }

    std::time_t now = std::time(nullptr);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y%m%d%H%M%S", std::localtime(&now));
    return std::string(folder_name) + "/Data_" + std::string(timestamp);
}

void displayReceivedData(int socket, const std::string& filename) {
    std::ofstream outfile(filename, std::ios::binary); // Open in binary mode
    if (!outfile.is_open()) {
        std::cerr << "Error: Unable to open file: " << filename << std::endl;
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;
    while ((bytes_received = recv(socket, buffer, sizeof(buffer), 0)) > 0) {
        outfile.write(buffer, bytes_received);
    }
    outfile.close();

    if (bytes_received < 0) {
        perror("recv");
    }
}
