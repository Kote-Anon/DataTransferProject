// serverHandler.cpp
#include "logHandler.cpp"
#include "fileHandler.cpp" // Include file handling logic
#include "dataTransferLog.cpp"
#include <thread>
#include <vector>


void handleClient(int client_socket) {
    std::string filename = generateFilename();
    std::cout << "Client connected. Receiving data and saving to file: " << filename << "\n";

    // Display received data
    displayReceivedData(client_socket, filename);

    // Log data transfer
    logDataTransfer(filename, client_socket);

    std::cout << "Data received and saved.\n";

    close(client_socket);
}

void runServer() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server started. Listening on port " << PORT << std::endl;

    std::vector<std::thread> threads;

    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        threads.emplace_back(handleClient, new_socket);
    }

    close(server_fd);
}