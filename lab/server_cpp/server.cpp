#include <iostream>      // std::cout, std::endl (for output)
#include <cstdlib>        // exit() (for error handling)
#include <cstring>        // std::memset() (for zeroing structs)
#include <unistd.h>       // close(), read(), write() (file descriptor operations)
#include <sys/socket.h>   // socket(), bind(), listen(), accept() (socket functions)
#include <netinet/in.h>   // sockaddr_in, INADDR_ANY, htons(), ntohs() (IPv4 address structures)
#include <arpa/inet.h>    // inet_ntoa() (convert IP address to string)

const int PORT = 8080;
const int BUFFER_SIZE = 1024;

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    
    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        exit(1);
    }
    
    // Enable SO_REUSEADDR: allows binding to a port that's still in TIME_WAIT state
    // Without this, if you stop and restart the server quickly, you'll get
    // "Address already in use" error (port stays in TIME_WAIT for ~30-120 seconds)
    // For a minimal server, this is optional but recommended for development
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    // Setup server address
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(1);
    }
    
    // Listen for connections
    if (listen(server_fd, 5) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(1);
    }
    
    std::cout << "TCP server listening on port " << PORT << std::endl;
    
    // Accept connection
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0) {
        perror("accept failed");
        close(server_fd);
        exit(1);
    }
    
    std::cout << "Client connected from " 
              << inet_ntoa(client_addr.sin_addr) << ":" 
              << ntohs(client_addr.sin_port) << std::endl;
    
    // Echo server: read and send back
    while (true) {
        ssize_t bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
        if (bytes_read <= 0) {
            break;
        }
        
        buffer[bytes_read] = '\0';
        std::cout << "Received: " << buffer;
        
        write(client_fd, buffer, bytes_read);
    }
    
    std::cout << "Client disconnected" << std::endl;
    close(client_fd);
    close(server_fd);
    
    return 0;
}

