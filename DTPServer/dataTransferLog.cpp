// dataTransferLog.cpp

#include <iostream>
#include <fstream>
#include <ctime>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

void logDataTransfer(const std::string& filename, const std::string& client_ip) {
    std::ofstream logfile("DTL.txt", std::ios::app);
    if (!logfile.is_open()) {
        std::cerr << "Error: Unable to open log file." << std::endl;
        return;
    }

    std::time_t now = std::time(nullptr);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    logfile << "Timestamp: " << timestamp << std::endl;
    logfile << "File Name: " << filename << std::endl;
    logfile << "Client IP: " << client_ip << std::endl;
    logfile << "------------------------------------" << std::endl;

    logfile.close();
}

void logDataTransfer(const std::string& filename, int client_socket) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    getpeername(client_socket, (struct sockaddr*)&client_addr, &client_addr_len);
    std::string client_ip = inet_ntoa(client_addr.sin_addr);

    logDataTransfer(filename, client_ip);
}