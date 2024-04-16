//fileHandler.cpp

#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring> // for strcmp
#include <thread>
#include <vector>
#include <ctime> // for timestamp
#include <sys/stat.h>
#include <filesystem> // for filesystem operations

#define PORT 8080
#define BUFFER_SIZE 1024

std::string generateFilename(const std::string& originalFilename) {
    // Create ReceivedFiles folder if it doesn't exist
    const std::string folder_name = "ReceivedFiles";
    std::filesystem::create_directory(folder_name);

    // Extract file extension from original filename
    size_t pos = originalFilename.find_last_of('.');
    std::string file_extension = (pos != std::string::npos) ? originalFilename.substr(pos) : "";

    // Generate unique filename with original file extension
    std::time_t now = std::time(nullptr);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y%m%d%H%M%S", std::localtime(&now));
    return folder_name + "/Data_" + std::string(timestamp) + file_extension;
}

void displayReceivedData(int socket, const std::string& originalFilename) {
    std::string filename = generateFilename(originalFilename);
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
