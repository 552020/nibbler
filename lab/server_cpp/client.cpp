#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const int PORT = 8080;
const int BUFFER_SIZE = 1024;
const char* SERVER_IP = "127.0.0.1";  // localhost

int main() {
    int client_fd;
    // sockaddr_in is the struct type (socket address for IPv4)
    // server_addr is the variable name - it holds the server's address (IP + port)
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    
    // Create socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("socket failed");
        exit(1);
    }
    
    // Setup server address structure (contains server's IP and port)
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    
    // Convert IP address from string to binary form
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("inet_pton failed");
        close(client_fd);
        exit(1);
    }
    
    // Connect to server
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        close(client_fd);
        exit(1);
    }
    
    std::cout << "Connected to server at " << SERVER_IP << ":" << PORT << std::endl;
    
    // Send message and receive echo
    const char* message = "Hello, server!\n";
    write(client_fd, message, strlen(message));
    
    ssize_t bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        std::cout << "Server echoed: " << buffer;
    }
    
    close(client_fd);
    return 0;
}

