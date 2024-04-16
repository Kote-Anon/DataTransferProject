#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Function to get the current date and time
std::string getCurrentDateTime() {
    // Get current date and time
    time_t now = time(0);
    struct tm *currentTime = localtime(&now);
    
    // Format the date and time
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", currentTime);
    return std::string(buffer);
}

// Function to get system information
std::string getSystemInfo() {
    std::ostringstream info;
    
    // Get hostname
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    info << "Hostname: " << hostname << ",";
    
    // Get username
    char username[256];
    getlogin_r(username, sizeof(username));
    info << "Username: " << username << ",";
    
    // Get IP address
    char ip[INET_ADDRSTRLEN];
    struct sockaddr_in sa;
    socklen_t len = sizeof(sa);
    if (getsockname(0, (struct sockaddr *)&sa, &len) == 0 && sa.sin_family == AF_INET) {
        inet_ntop(AF_INET, &sa.sin_addr, ip, sizeof(ip));
        info << "IP Address: " << ip << ",";
    } else {
        info << "IP Address: Unknown,";
    }
    
    // Get localization information (latitude and longitude)
    // You can replace these values with actual latitude and longitude obtained from a localization service
    double latitude = 0.0; // Example latitude
    double longitude = 0.0; // Example longitude
    info << "Latitude: " << latitude << ",";
    info << "Longitude: " << longitude << ",";
    
    // Get operating system
    #ifdef _WIN32
        info << "Operating System: Windows,";
    #elif _WIN64
        info << "Operating System: Windows,";
    #elif __APPLE__ || __MACH__
        info << "Operating System: MacOS,";
    #elif __linux__
        info << "Operating System: Linux,";
    #elif __FreeBSD__
        info << "Operating System: FreeBSD,";
    #elif __unix || __unix__
        info << "Operating System: Unix,";
    #else
        info << "Operating System: Unknown,";
    #endif
    
    // Get current date and time
    info << "Date and Time: " << getCurrentDateTime();
    
    return info.str();
}

// Function to save system information to a CSV file
void saveSystemInfoToCSV() {
    // Get system information
    std::string systemInfo = getSystemInfo();
    
    // Open the CSV file for writing
    std::ofstream outFile("ComputerData.csv", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open ComputerData.csv for writing\n";
        return;
    }
    
    // Write system information to the CSV file
    outFile << systemInfo << std::endl;
    
    // Close the CSV file
    outFile.close();
    
    std::cout << "System information saved to ComputerData.csv" << std::endl;
}
