#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>

#define DEFAULT_BUFFER_SIZE 1024

// Function to send a file from client to server
bool sendFile(const char* filename, const char* ip, int port, int buffer_size = DEFAULT_BUFFER_SIZE) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation error: " << strerror(errno) << std::endl;
        return false;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return false;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed: " << strerror(errno) << std::endl;
        return false;
    }

    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        close(sock);
        return false;
    }

    char buffer[buffer_size];
    ssize_t total_bytes_sent = 0;
    ssize_t bytes_read;
    while ((bytes_read = file.read(buffer, sizeof(buffer)).gcount()) > 0) {
        ssize_t bytes_sent = send(sock, buffer, bytes_read, 0);
        if (bytes_sent < 0) {
            std::cerr << "Error in sending data: " << strerror(errno) << std::endl;
            file.close();
            close(sock);
            return false;
        }
        total_bytes_sent += bytes_sent;
    }

    std::cout << "File sent successfully. Total bytes sent: " << total_bytes_sent << std::endl;
    file.close();
    close(sock);
    return true;
}

// Function to receive a file from client
bool receiveFile(const char* filename, int client_socket, int buffer_size = DEFAULT_BUFFER_SIZE) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Unable to create file: " << filename << std::endl;
        return false;
    }

    char buffer[buffer_size];
    ssize_t total_bytes_received = 0;
    ssize_t bytes_received;
    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        file.write(buffer, bytes_received);
        total_bytes_received += bytes_received;
    }

    if (bytes_received < 0) {
        std::cerr << "Error in receiving data: " << strerror(errno) << std::endl;
        file.close();
        return false;
    }

    std::cout << "File received successfully. Total bytes received: " << total_bytes_received << std::endl;
    file.close();
    return true;
}
